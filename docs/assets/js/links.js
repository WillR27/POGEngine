var rootURL = window.location.host;

window.onload = function() {
    $.getJSON("//" + rootURL + "/assets/data/links.json", function(json) {
        console.log(json);

        json.links.forEach(link => {
            $('a[href="link::' + link.key + '"]').each(function() {
                $(this).attr('href', window.location.protocol + "//" + rootURL + "/" + link.link);
            });
        });
    });
}