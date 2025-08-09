#pragma once
#include <Update.h>
#include <Resources/Html.h>
extern WebServer server;

String buildFullBody(String content, const char* activeMenu = nullptr) {
    String placeholder = "{{";
    placeholder += activeMenu;
    placeholder += "}}";

    String html = global_htmlTemplate;
    html.replace("{{content}}", content);
    html.replace(placeholder, "active");
    html.replace("{{version}}", global_version);

    return html;
}

class Routing {
public:
    void init() {
        server.on("/", []() {
            String html = global_htmlHome;
            html.replace("{{oil_temp}}", "97");
            html.replace("{{water_temp}}", "90");
            html.replace("{{clock_time}}", "10:20");
            html.replace("{{clock_date}}", "10.05.2025");
            html.replace("{{air_temp}}", "25");

            server.send(
                200,
                "text/html",
                buildFullBody(html, "home")
            );
        });
        server.on("/settings", []() {
            server.send(
                200,
                "text/html",
                buildFullBody(global_htmlSettingsForm, "settings")
            );
        });
        server.on("/firmware", HTTP_GET, []() {
            server.send(
                200,
                "text/html",
                buildFullBody(global_htmlFirmwareUploadForm, "firmware")
            );
        });

        server.on(
            "/firmware",
            HTTP_POST,
            []() {
                bool success = !Update.hasError();
                server.send(200, "text/html", buildFullBody(
                    success
                    ? "<h2>✅ Firmware updated successfully. Rebooting...</h2><p><a class=\"link-back\" href=\"/firmware\">Back</a></p>"
                    : "<h2>❌ Firmware update failed!</h2><p><a class=\"link-back\" href=\"/firmware\">Back</a></p>",
                    "firmware"
                ));
                delay(1000);
                if (success) {
                    ESP.restart();
                }
            },
            []() {
                HTTPUpload& upload = server.upload();

                if (upload.status == UPLOAD_FILE_START) {
                    if (!Update.begin()) {
                        Update.printError(Serial);
                    }
                } else if (upload.status == UPLOAD_FILE_WRITE) {
                    if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
                        Update.printError(Serial);
                    }
                } else if (upload.status == UPLOAD_FILE_END) {
                    if (!Update.end(true)) {
                        Update.printError(Serial);
                    }
                }
            }
        );

        server.on("/about", []() {
            server.send(
                200,
                "text/html",
                buildFullBody(global_htmlAbout, "about")
            );
        });
    }
};