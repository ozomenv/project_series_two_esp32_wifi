const char* global_htmlTemplate = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8">
  <title>ESP32 Web Interface</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    h1{
      margin-block-end: 0.50em;
      margin-block-start: 0.50em;
    }
    body {
      font-family: Arial, sans-serif;
      margin: 0;
      padding: 0;
      min-height: 100%;
      min-height: 100svh;
      min-height: 100dvh;
      display: flex;
      flex-direction: column;
      margin: 0;
    }
    .navbar {
      background-color: #333;
      overflow: hidden;
    }
    .link-back {
      font-size: 22px;
    }
    .navbar {
      background: #333;
      display: flex;
      flex-wrap: wrap;
      justify-content: flex-start;
      gap: 4px 10px;
      padding: 6px 8px;
    }
    .navbar a {
      color: #f2f2f2;
      text-decoration: none;
      padding: 10px 14px;
      font-size: 16px;
      border-radius: 4px;
    }
    .navbar a:hover,
    .navbar a.active { background:#ddd; color:#000; }
    @media (max-width: 420px) {
      .navbar { justify-content: center; }
      .navbar a { font-size: 14px; padding: 8px 10px; }
    }
    .content {
      padding: 0px 20px 20px 20px;
      flex: 1 0 auto;
      padding-bottom: calc(var(--footer-h) + 20px);
    }
    :root {
      --footer-h: 54px;
      --space-1: 8px;
      --space-2: 12px;
      --space-3: 16px;
      --space-4: 20px;
    }
    .footer {
      margin-top: auto;
      position: fixed;
      bottom: 0;
      left: 0;
      right: 0;
      height: var(--footer-h);
      display: flex; align-items: center; justify-content: center;
      background: #868585; color:#fff; font-size:14px; padding:0 10px;
    }
    @media (max-width: 480px) {
      .footer { position: static; height:auto; }
      .content { padding-bottom: 20px; }
    }
    .cards {
      display: grid;
      grid-auto-rows: 1fr;
      grid-template-columns: repeat(2, 360px);
      justify-content: center;
      gap: 20px;
    }

    .card {
      max-width: 90vw;
      background: #fff;
      border-radius: 12px;
      padding: 16px 18px;
      box-shadow: 0 4px 14px rgb(0 0 0 / 32%);
      text-align: center;
    }

    .card .label {
      font-size: 14px;
      color: #666;
      margin-bottom: 6px;
      display: flex;
      align-items: center;
      justify-content: center;
      gap: 8px;
    }

    .card .value {
      font-size: 44px;
      font-weight: 600;
      line-height: 1.1;
    }

    .card .unit {
      font-size: 20px;
      margin-left: 6px;
      color: #666;
    }

    .sub {
      font-size: 16px;
      color: #444;
      margin-top: 6px;
    }

    @media (max-width: 820px) {
      .cards {
        grid-template-columns: 1fr;
        justify-items: center;
      }
      .card {
        width: min(360px, 100% - 24px);
      }
    }


    .form-card{
      max-width: 720px;
      margin: 0 auto;
      background:#fff;
      border-radius:12px;
      padding:16px 18px;
      box-shadow:0 4px 14px rgba(0,0,0,.12);
      padding: var(--space-3) var(--space-4);
    }

    .form-grid{
      display:grid;
      gap:12px;
      row-gap: var(--space-3);
    }
    .form-grid.two-col{
      grid-template-columns: repeat(2, minmax(0,1fr));
      column-gap: var(--space-4);
    }

    @media (max-width: 640px){
      .form-grid.two-col{ grid-template-columns: 1fr; }
    }

    .form-field{
      display:flex;
      flex-direction:column;
      margin-bottom: var(--space-3);
    }
    .form-field label{
      font-size:16px;
      margin-bottom:6px;
      color:#333;
      margin-bottom: var(--space-1);
      line-height: 1.25;
    }
    .form-field input[type="date"],
    .form-field input[type="time"],
    .form-field select{
      width:100%; font-size:16px; padding:10px 12px;
      border:1px solid #ccc; border-radius:8px; background:#fff;
      box-sizing: border-box;
    }

    .toggle{
      display: grid;
      grid-template-columns: 1fr 1fr;
      width: min(340px, 100%);
      margin-top: 6px;
      border: 1px solid #d0d0d0;
      border-radius: 9999px;
      overflow: hidden;
      background: #f1f3f5;
      margin-top: var(--space-1);
      margin-bottom: var(--space-2);
    }
    .toggle input{ display:none; }
    .toggle label{
      margin: 0;
      padding: 10px 0;
      text-align: center;
      font-size: 16px;
      cursor: pointer;
      user-select: none;
      line-height: 1;
    }
    .toggle input:checked + label{
      background: #0aa76b;
      color: #fff;
    }

    .toggle label:first-of-type{ border-right: 1px solid #d0d0d0; }

    .form-actions{
      display: flex;
      justify-content: center;
      margin-top: 14px;
      margin-top: var(--space-4);
    }
    select, input[type="date"], input[type="time"] {
      margin-top: var(--space-1);
    }
    .btn-primary{
      width: min(320px, 100%);
      font-size: 18px;
      padding: 12px 16px;
      border: 0;
      border-radius: 10px;
      background: #333;
      color: #fff;
      cursor: pointer;
    }
    .btn-primary:active{ transform: translateY(1px); }
  </style>
</head>
<body>
  <div class="navbar">
    <a href="/" class="{{home}}">Home</a>
    <a href="/settings" class="{{settings}}">Settings</a>
    <a href="/firmware" class="{{firmware}}">Firmware Update</a>
    <a href="/about" class="{{about}}">About</a>
  </div>
  <div class="content">
    {{content}}
  </div>
  <footer class="footer">
    <p>© 2025 Ozomen | Firmware v{{version}}</p>
  </footer>
</body>
</html>
)rawliteral";

const char* global_htmlAbout = R"rawliteral(
<h1>About</h1>
<p>This device was developed by an enthusiast from Ukraine specifically for the Citroen car. The development was carried out only on his own initiative and at his own time and expense. The panel was designed to replace the standard panel and provide new functionality. The software is open source and developed for Arduino.</p>
)rawliteral";

const char* global_htmlFirmwareUploadForm = R"rawliteral(
<h1>Firmware Update</h1>

<p style="color: red; font-weight: bold;">
⚠️ Warning: Uploading an incorrect firmware file may damage your device.<br>
Do not turn off the power or close this page during the update process.
</p>
<br>
<form method="POST" action="/firmware" enctype="multipart/form-data">
  <input type="file" name="firmware" accept=".bin" required>
  <br><br>
  <input type="submit" value="Update" style="font-size: 24px;">
</form>
)rawliteral";

const char* global_version = R"rawliteral(
1.0.1
)rawliteral";

const char* global_htmlHome = R"rawliteral(
<h1>Main</h1>

<div class="cards">
  <div class="card">
    <div class="label">🛢️ Oil temp</div>
    <div class="value">
      <span id="oilTemp">{{oil_temp}}</span><span class="unit">°C</span>
    </div>
  </div>

  <div class="card">
    <div class="label">🌡️ Water temp</div>
    <div class="value">
      <span id="coolantTemp">{{water_temp}}</span><span class="unit">°C</span>
    </div>
  </div>

  <div class="card">
    <div class="label">⏰ Clock</div>
    <div class="value" style="font-size:38px;">
      <span id="clock">{{clock_time}}</span>
    </div>
    <div class="sub" id="date">{{clock_date}}</div>
  </div>

  <div class="card">
    <div class="label">🌤️ Air temp</div>
    <div class="value">
      <span id="outsideTemp">{{air_temp}}</span><span class="unit">°C</span>
    </div>
  </div>
</div>
)rawliteral";


const char* global_htmlSettingsForm = R"rawliteral(
<h1>Settings</h1>

<br>
<div class="form-card">
  <form method="POST" action="/settings">
    <div class="form-grid two-col">
      <div class="form-field">
        <label for="date">Date</label>
        <input type="date" id="date" name="date" required>
      </div>
      <div class="form-field">
        <label for="time">Time</label>
        <input type="time" id="time" name="time" required>
      </div>
    </div>

    <div class="form-field">
      <label>Encoder sound</label>
      <div class="toggle">
        <input type="radio" id="enc_on"  name="encoder_sound" value="on"  checked>
        <label for="enc_on">On</label>
        <input type="radio" id="enc_off" name="encoder_sound" value="off">
        <label for="enc_off">Off</label>
      </div>
    </div>

    <div class="form-field">
      <label>Warning sound</label>
      <div class="toggle">
        <input type="radio" id="warn_on"  name="warning_sound" value="on"  checked>
        <label for="warn_on">On</label>
        <input type="radio" id="warn_off" name="warning_sound" value="off">
        <label for="warn_off">Off</label>
      </div>
    </div>

    <div class="form-field">
      <label>Night mode</label>
      <div class="toggle">
        <input type="radio" id="night_on"  name="night_mode" value="on"  checked>
        <label for="night_on">On</label>
        <input type="radio" id="night_off" name="night_mode" value="off">
        <label for="night_off">Off</label>
      </div>
    </div>

    <div class="form-field">
      <label for="brightness">Display brightness</label>
      <select id="brightness" name="brightness">
        <option value="0">1</option>
        <option value="40">2</option>
        <option value="85">3</option>
        <option value="110">4</option>
        <option value="135">5</option>
        <option value="160">6</option>
        <option value="185">7</option>
        <option value="210">8</option>
        <option value="230">9</option>
        <option value="255">10</option>
      </select>
    </div>

    <br>
    <button class="btn-primary" type="submit">Update</button>
  </form>
</div>
)rawliteral";