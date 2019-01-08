import QtQuick 2.2
import QtQuick.Controls 1.1
import QtWebView 1.1

WebView {
        id: webView
        //anchors.fill: parent doesn't for webengine
        focus: true
        width: 720
        height: 480
        signal pageLoaded(string url)
        signal jsResult(string result)
        onLoadingChanged: {
            console.log("onLoadingChanged: status=" + loadRequest.status);
            if (loadRequest.status == WebView.LoadStartedStatus)
                console.log("Loading started...");
            else if (loadRequest.status == WebView.LoadFailedStatus) {
               console.log("Load failed! Error code: " + loadRequest.errorCode);
               //if (loadRequest.errorCode === NetworkReply.OperationCanceledError)
               //    console.log("Load cancelled by user");
            } else if (loadRequest.status == WebView.LoadSucceededStatus) {
                console.log("Page loaded:" + url)
                pageLoaded(url)
            }
        }

        function evalJS(js) {
          webView.runJavaScript(js, function(result) { 
            console.log(result); 
            jsResult(result);
          });
        }
        function forward() {
          webView.goForward();
        }
        function back() {
          webView.goBack();
        }
        function forceFocus() {
          webView.forceActiveFocus();
        }
}
