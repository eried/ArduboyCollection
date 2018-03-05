<?php
require 'config.php';
@$s=$_GET['secret'];
if($s!=$secret_keywords) // Prevent abuse
  die('Not available');

if(!file_exists('pending_run'))
  die('Exited');

echo 'Starting update';
unlink('pending_run');

/* gets the data from a URL */
function get_data($url)
{
	$ch = curl_init();
	$timeout = 30;
	curl_setopt($ch, CURLOPT_URL, $url);
	curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
	curl_setopt($ch,CURLOPT_USERAGENT,'Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US; rv:1.8.1.13) Gecko/20080311 Firefox/2.0.0.13');
	curl_setopt($ch, CURLOPT_CONNECTTIMEOUT, $timeout);
	$data = curl_exec($ch);
	curl_close($ch);
	return $data;
}

// UTF8 Encode
function utf8ize($d)
{
    if (is_array($d))
        foreach ($d as $k => $v)
            $d[$k] = utf8ize($v);

     else if(is_object($d))
        foreach ($d as $k => $v)
            $d->$k = utf8ize($v);

     else
        return utf8_encode($d);

    return $d;
}

// Get repository
$repo = json_decode(get_data("https://api.github.com/repos/{$repopath}git/trees/master?recursive=1&client_id={$client_id}&client_secret={$client_secret}"));

// Generate output json
$output = array();

foreach($repo->tree as $f)
{
  $info = pathinfo($f->path);
  @$s = $info["extension"];

  if(strlen($s)>0)
  {

    // Special case for source.url
    if($info["filename"] == 'source')
      $s='sourceurl';

    $path = $info["dirname"] /*. "/" . $info["filename"]*/;
    $output[$path][strtolower($s)] = $f->path;
  }
}

?><pre><?php print_r($output); ?></pre><?php // */

// Get URL
function get_url($s)
{
  $url = '';

  if(strlen($s)>0)
  {
    $ss = get_data(g($s));
    $url = trim(array_reverse(explode('URL=',$ss))[0]);
  }

  return $url;
}

// Full path
function g($p)
{
  global $server, $repopath;

  $p=rawurlencode($p);
  return "{$server}{$repopath}master/{$p}";
}

// URL exist, from: http://www.barattalo.it/coding/test-if-a-remote-url-exists-with-php-and-curl/
function url_exists($url)
{
    $h = get_headers($url);
    $status = array();
    preg_match('/HTTP\/.* ([0-9]+) .*/', $h[0] , $status);
    return ($status[1] == 200);
}

$files = array();
$names = array();

echo 'Parsing output';
foreach($output as $k => $f)
{
  if(strlen($k)>3)
  {
    $info = pathinfo($k);
    $title = $info["basename"];
    @$bin = (string)($output[$k]['hex']);

    //echo $k . ' value: ' . $f;
    /*?><pre><?php print_r($output[$k]['hex']); ?></pre><?php // */

    if(strlen($bin)>0)
    {
      $genre = $info["dirname"];
      @$s = $output[$k]['txt'];
      @$description = strlen($s)>0?get_data(g($s)):'';

      // Get other data
      $author = 'Unknown';
      $modified = '2017-01-01T12:00:00Z';
      $license = '';

      @$s = $output[$k]['ini'];

      if(strlen($s)>0)
      {
        $ini = parse_ini_string(get_data(g($s)),FALSE,INI_SCANNER_RAW);

        if(strlen($ini['author'])>0)
          $author = $ini['author'];

        if(strlen($ini['date'])>0)
          $modified = $ini['date'];

        // Remote hex location
        if(@strlen($ini['hex'])>0)
        {
          if(url_exists($ini['hex']))
            $bin = $ini['hex'];
        }

        if(strlen($ini['description'])>0)
          $description = $ini['description'];

        if(@strlen($ini['title'])>0)
          $title = $ini['title'];

        if(@strlen($ini['license'])>0)
          $license = $ini['license'];
      }

      // Get URL
      @$url = get_url($output[$k]['url']);
      @$sourceUrl = get_url($output[$k]['sourceurl']);

      if(strlen($sourceUrl)==0)
        $sourceUrl = $url;

      $screenshots = array();
      $hex = array(array("title"=>$title,"filename"=>g($bin),"device"=>"Arduboy"));;

      @$s = $output[$k]['png'];
      $banner = strlen($s)>0?g($s):'';

      if(strlen($banner)<=3)
      {
        @$s = $output[$k]['jpg'];
        $banner = strlen($s)>0?g($s):'';
      }

      $names[] = $title;
      $files[] = array("title"=>trim($title),
      "description"=>trim($description),
      "genre"=>$genre,"url"=>$url,"sourceUrl"=>$sourceUrl,"author"=>$author,"banner"=>$banner,"date"=>$modified,"binaries"=>$hex,"screenshots"=>$screenshots,"license"=>$license, "arduboy"=>"");
    }
  }
}

echo '<br>Writing results';

// Sorting
array_multisort($names,SORT_STRING | SORT_FLAG_CASE,$files);

$values = array("repository"=>"Erwin's Arduboy Collection", "api-version"=>"1.0", "email"=>"", "maintainer"=>"Erwin Ried","website"=>"http://ried.cl","items"=>array_values($files));
file_put_contents("repo.json",json_encode(utf8ize($values),JSON_HEX_TAG | JSON_HEX_APOS | JSON_HEX_QUOT | JSON_HEX_AMP | JSON_PRETTY_PRINT));

// Mode debug
echo '<br>json encode result: ';
echo json_last_error();
echo '<br>';
print_r($values);
echo '<br>';
echo '<br>';


echo  json_last_error();

echo 'Creating website';

//register mustache library
require 'Mustache/Autoloader.php';
Mustache_Autoloader::register();

$template = file_get_contents("template.html");

//start the mustache engine
$m = new Mustache_Engine;
file_put_contents("index.html",$m->render($template, $values));

echo '<br>Done';
