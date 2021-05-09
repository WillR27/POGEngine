////////////////////////////////////////////////////
// Setup

var rootURL = window.location.host;
var extraURL = "";
var pathName = window.location.pathname;

if (rootURL.includes("github")) {
    extraURL = "/POGEngine";
}

rootURL += extraURL;
pathName.replace(extraURL, "");

// Setup
////////////////////////////////////////////////////

////////////////////////////////////////////////////
// Links

window.onload = function() {
    $.getJSON("//" + rootURL + "/assets/data/links.json", function(json) {
        json.links.forEach(link => {
            $('a[href="::' + link.key + '"]').each(function() {
                $(this).attr('href', window.location.protocol + "//" + rootURL + "/" + link.link);
            });
        });
    });
}

// Links
////////////////////////////////////////////////////

////////////////////////////////////////////////////
// Navbar

$(function() {
    function expand(subsection) {
        var $childList = $(subsection).children("ul");
        var $div = $(subsection).children("div");

        if (!$div.hasClass("expanded")) {
            $childList.show(); 
            $div.addClass("expanded");
        }
    }

    function collapse(subsection) {
        var $childList = $(subsection).children("ul");
        var $div = $(subsection).children("div");

        if ($div.hasClass("expanded")) {
            $childList.hide(); 
            $div.removeClass("expanded");
        }
    }

    function toggle(subsection) {
        var $div = $(subsection).children("div");

        if ($div.hasClass("expanded")) {
            collapse(subsection);
        } else {
            expand(subsection);
        }
    }

    function loop(subsection) {
        var isOpen = false;
        var hasChildren = false;
    
        var $childList = $(subsection).children("ul");
    
        $childList.children("li").each(function() {
            hasChildren = true;
    
            if (loop(this)) {
                isOpen = true;
            }
        });
        
        var href = $(subsection).children("a").attr("href");
        if (href === pathName) {
            isOpen = true;
        }
    
        var $div = $(subsection).children("div");
    
        if (isOpen) {
            expand(subsection);
        } else {
            $childList.hide();
        }
    
        if (hasChildren) {
            $div.click(function() {
                toggle(subsection);
            });
        } else {
            $div.addClass("empty");
        }
    
        return isOpen;
    }

    $("nav .section").children("ul").children("li").each(function() {
        loop(this);
    });
});

// Navbar
////////////////////////////////////////////////////