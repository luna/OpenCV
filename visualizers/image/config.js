module.exports = function (t) {
    var placeholderVis = {name: "image", path: "image.html"};
    return t.constructor == 'Image' ? [placeholderVis] : [];
};
