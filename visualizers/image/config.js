var cfgHelper = require("../visualization-config-helper.js")

module.exports = function (type) {
    var visPattern =
        { constructor: ["Image"], fields: [{constructor: ["Int", "Real"], fields: { any: true }}]
        };

    if (cfgHelper.matchesType(type, visPattern))
        {
            return [{name: "image", path: "image.html"}]
        }
    else
        return [];
};
