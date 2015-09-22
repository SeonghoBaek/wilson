/**
 * Created by major on 9/8/14.
 */
var express = require('express');
var router = express.Router();
var fs = require('fs');
var nbus = require('./nodebus');

var NODE_NAME = "wilson.node";
var BIGNODE_NAME = "bignode.node";

var nodeCallback = function (data) {
    console.log(data +'\n');
};

nbus.join(NODE_NAME, nodeCallback, false);

router.get('/', function(req, res) {
    console.log("Welcome to wilson");
    fs.readFile('wilson/wilson.html', function(err, data) {
        if (err) console.log(err);
        res.writeHead(200, { 'Content-Type': 'text/html' });
        res.end(data);
    });
});

router.post('/', function(req, res, next) {
    req.pipe(req.busboy);

    req.busboy.on('file', function(fieldName, file, fileName) {
        if (fileName == '') {
            console.log("fileName is null");
            res.redirect('/');

            return;
        }

            console.log("Uploading: " + fileName);

            var fstream = fs.createWriteStream(__dirname + fileName);
            file.pipe(fstream);
            fstream.on('close', function() {
                console.log("Upload Finished of " + fileName);
                res.redirect('/');

            // Cast XML.
            fs.readFile(__dirname + fileName, function(err, data) {
                nbus.cast(BIGNODE_NAME, data.toString(), BC_CLIENT_MESSAGE);
                fs.unlinkSync(__dirname + fileName);
            });
        });
    });

    req.busboy.on('field', function(key, value) {
        console.log(key +" " + value);
    });
});

module.exports = router;











