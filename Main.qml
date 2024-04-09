import QtQuick 2.12
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import ImageDownloader 1.0

ApplicationWindow {
    visible: true
    width: 800
    height: 600
    title: "Image Downloader"

    MainImageDownloader {
        id: imageDownloader
    }

    function downloadImage(url, filename, index) {
        imageDownloader.downloadImage(url, filename);
        imageDownloader.downloadProgress.connect(function(counter, received, total) {
            if (counter === index) {
                urlInputs.itemAt(index).children[0].children[2].value = received / total;
            }
        });
    }

    ColumnLayout {
        anchors.fill: parent
        Repeater {
            id: urlInputs
            model: 10
            Rectangle {
                Layout.fillWidth: true
                Layout.minimumHeight: 50
                color: "lightgray"
                RowLayout {
                    anchors.fill: parent
                    TextField {
                        id: textField
                        Layout.fillWidth: true
                        placeholderText: "Enter Image URL"
                    }
                    Image {
                        Layout.preferredHeight: 50
                        Layout.preferredWidth: 50
                        source: textField.text
                    }
                    ProgressBar { // Исправлено
                        id: progressBar
                        Layout.fillWidth: true
                        from: 0
                        to: 1
                    }
                }
            }
        }

        Button {
            text: "Download Images"
            onClicked: {
                for (var i = 0; i < urlInputs.count; i++) {
                    var url = urlInputs.itemAt(i).children[0].children[0].text
                    if (url !== "") {
                        var filename = "image_" + i + ".jpg"
                        downloadImage(url, filename, i)
                    }
                }
            }
        }
    }
}
