
function initFilter( _settings ){
    var settings = {
        boxSelector: ".box",
        categoryElement: '#category',
        searchElement: '#search',
        sortElement: 'btn-toggle[data-sort-by]',
        newOnlyElement: '#newOnly',
        libreOnlyElement: '#libreOnly',
        categoryAttribute: "data-item-tags",
        dateAttribute: "data-item-date",
        licenseAttribute: "data-item-license",
        newDateCutoff: 30, // days

        newOnly:false,
        libreOnly:false,
        currentCategory:'',
        sort: 'data-item-timestamp',
        sortAsc:false,
        search: ''
    };

    var categories = {}, boxes = [], parent;

    // Libre licenses
    var libreLicenses = ["AAL","AFL-1.1","AFL-1.2","AFL-2.0","AFL-2.1","AFL-3.0","AGPL-3.0-only","AGPL-3.0-or-later","Apache-1.1","Apache-2.0","APL-1.0","APSL-1.0","APSL-1.1","APSL-1.2","APSL-2.0","Artistic-1.0-cl8","Artistic-1.0-Perl","Artistic-1.0","Artistic-2.0","BSD-2-Clause-Patent","BSD-2-Clause","BSD-3-Clause","BSL-1.0","CATOSL-1.1","CC0-1.0","CDDL-1.0","CECILL-2.1","CNRI-Python","CPAL-1.0","CPL-1.0","CUA-OPL-1.0","ECL-1.0","ECL-2.0","EFL-1.0","EFL-2.0","Entessa","EPL-1.0","EPL-2.0","EUDatagrid","EUPL-1.1","EUPL-1.2","Fair","Frameworx-1.0","GPL-2.0-only","GPL-2.0-or-later","GPL-3.0-only","GPL-3.0-or-later","HPND","Intel","IPA","IPL-1.0","ISC","LGPL-2.0-only","LGPL-2.0-or-later","LGPL-2.1-only","LGPL-2.1-or-later","LGPL-3.0-only","LGPL-3.0-or-later","LiLiQ-P-1.1","LiLiQ-R-1.1","LiLiQ-Rplus-1.1","LPL-1.0","LPL-1.02","LPPL-1.3c","MirOS","MIT","Motosoto","MPL-1.0","MPL-1.1","MPL-2.0-no-copyleft-exception","MPL-2.0","MS-PL","MS-RL","Multics","NASA-1.3","Naumen","NCSA","NGPL","Nokia","NPOSL-3.0","NTP","OCLC-2.0","OFL-1.1","OGTSL","OSET-PL-2.1","OSL-1.0","OSL-2.0","OSL-2.1","OSL-3.0","PHP-3.0","PostgreSQL","Python-2.0","QPL-1.0","RPL-1.1","RPL-1.5","RPSL-1.0","RSCPL","SimPL-2.0","SISSL","Sleepycat","SPL-1.0","UPL-1.0","VSL-1.0","W3C","Watcom-1.0","Xnet","Zlib","ZPL-2.0","AGPL-3.0","GPL-2.0+","GPL-2.0","GPL-3.0+","GPL-3.0-with-GCC-exception","GPL-3.0","LGPL-2.0+","LGPL-2.0","LGPL-2.1+","LGPL-2.1","LGPL-3.0+","LGPL-3.0"];
    function isLibre(license) {
      return libreLicenses.indexOf(license) != -1;
    }

    // merge incoming settings object, overwriting defaults above
    for( var k in _settings )
        settings[k] = _settings[k];

    // calculate cutoff date
    var cutoff = (new Date()).setDate( - settings.newDateCutoff );

    // discover existing categories
    var boxList = document.body.querySelectorAll( settings.boxSelector );
    for( var i=0, box; box=boxList[i++]; ){

        var tags = box.getAttribute( settings.categoryAttribute ) || "";
        var date = (new Date(box.getAttribute( settings.dateAttribute ))).getTime();
        var license = box.getAttribute( settings.licenseAttribute ) || "";

        // get the element that contains the title
        var title = box.querySelector("H3");
        if( title ){
            var text = "";

            // find the author's name and save it in an attribute
            var author = title.querySelector("A");
            if( author )
                box.setAttribute( "data-item-author", author.textContent );

            // use the rest of the text for the item's title
            for( var c=0, child; child=title.childNodes[c++]; ){
                if( child.nodeType == child.TEXT_NODE )
                    text += child.textContent;
            }
            box.setAttribute("data-item-title", text.replace(/by\s*$/, '') );
            boxes.push( box );

        }

        // store parsed date for easier sorting
        box.setAttribute( "data-item-timestamp", date );
        box.setAttribute("data-item-new", date > cutoff );
        box.setAttribute("data-item-libre", isLibre(license));

        tags = tags.split(/\s*,\s*/);
        // add tags to hashset
        for( var j=0; j<tags.length; ++j )
            categories[ tags[j] ] = tags[j];

        parent = box.parentElement;
    }

    // populate the category drop-down
    var select = document.querySelector( settings.categoryElement );
    for( var k in categories ){
        var option = document.createElement("option");
        option.textContent = option.value = k;
        select.appendChild( option );
    }
    select.addEventListener('change', function(){
        settings.currentCategory = select.value;
        updateFilter();
    });

    var input = document.querySelector( settings.searchElement );
    input.addEventListener('change', function(){
        settings.search = input.value.trim();
        updateFilter();
    });

    var sorts = document.body.querySelectorAll( settings.sortElement );
    for( var i=0, sort; sort=sorts[i]; ++i ){
        sort.classList.add("sort-" + sort.getAttribute("data-sort-by") );
        sort.addEventListener('click', function( evt ){
            var sort = evt.target;
            var key = sort.getAttribute("data-sort-by");
            if( settings.sort == key )
                sort.classList.toggle("asc");
            sort.parentElement.setAttribute("data-current-sort", key);
            settings.sort = key;
            settings.sortAsc = sort.classList.contains("asc");
            updateFilter();
        });
    }

    var newOnly = document.body.querySelector( settings.newOnlyElement );
    newOnly.addEventListener('click', function( evt ){
        settings.newOnly = newOnly.classList.toggle('active');
        updateFilter();
    });

    var libreOnly = document.body.querySelector( settings.libreOnlyElement );
    libreOnly.addEventListener('click', function( evt ){
        settings.libreOnly = libreOnly.classList.toggle('active');
        updateFilter();
    });

    updateFilter();

    return;

    function updateFilter(){
        for( var i=0, box; box=boxes[i++]; ){
            if( box.parentElement )
                parent.removeChild( box );
        }

        boxes = boxes.sort(function( a, b ){
            a = a.getAttribute( settings.sort ).toLowerCase();
            b = b.getAttribute( settings.sort ).toLowerCase();
            var v = settings.sortAsc ? 1 : -1;

            if( a > b ) return v;
            if( b > a ) return -v;
            return 0;
        });

        for( var i=0, box; box=boxes[i++]; ){
            var visible = true;
            if( visible && settings.currentCategory ){
                visible = box.getAttribute( settings.categoryAttribute ).split(/\s*,\s*/).indexOf( settings.currentCategory ) != -1;
            }

            if( visible && settings.newOnly ){
                visible = box.getAttribute("data-item-new") == "true";
            }

            if( visible && settings.libreOnly ){
                visible = box.getAttribute("data-item-libre") == "true";
            }

            if( visible && settings.search ){
                visible = box.textContent.toLowerCase().indexOf( settings.search.toLowerCase() ) != -1;
            }

            if( visible ){
                parent.appendChild( box );
            }

        }

    }

}
