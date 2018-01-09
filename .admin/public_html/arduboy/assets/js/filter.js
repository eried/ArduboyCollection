
function initFilter( _settings ){
    var settings = {
        boxSelector: ".box",
        categoryElement: '#category',
        searchElement: '#search',
        sortElement: 'btn-toggle[data-sort-by]',
        newOnlyElement: '#newOnly',
        categoryAttribute: "data-item-tags",
        dateAttribute: "data-item-date",
        newDateCutoff: 30, // days

        newOnly:false,
        currentCategory:'',
        sort: 'data-item-title',
        sortAsc:true,
        search: ''
    };

    var categories = {}, boxes = [], parent;

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

            if( visible && settings.search ){
                visible = box.textContent.toLowerCase().indexOf( settings.search.toLowerCase() ) != -1;
            }

            if( visible ){
                parent.appendChild( box );
            }
            
        }
        
    }

}
