// const char index_html[] PROGMEM = R"rawliteral(
// <!DOCTYPE html>
// <html>
// <head>
//   <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1, user-scalable=no">
//   <style>
//     .arrows {
//       font-size: 40px;
//       color: red;
//       user-select: none;
//     }
//     td.button {
//       background-color: black;
//       border-radius: 25%;
//       box-shadow: 5px 5px #888888;
//       text-align: center;
//       cursor: pointer;
//       user-select: none;
//       -webkit-tap-highlight-color: transparent;
//     }
//     td.button:active {
//       transform: translate(5px, 5px);
//       box-shadow: none;
//     }
//     .slidecontainer {
//       width: 100%;
//     }
//     .slider {
//       -webkit-appearance: none;
//       width: 100%;
//       height: 15px;
//       border-radius: 5px;
//       background: #d3d3d3;
//       outline: none;
//       opacity: 0.7;
//       -webkit-transition: .2s;
//       transition: opacity .2s;
//     }
//     .slider:hover {
//       opacity: 1;
//     }
//     .slider::-webkit-slider-thumb {
//       -webkit-appearance: none;
//       appearance: none;
//       width: 25px;
//       height: 25px;
//       border-radius: 50%;
//       background: red;
//       cursor: pointer;
//     }
//     .slider::-moz-range-thumb {
//       width: 25px;
//       height: 25px;
//       border-radius: 50%;
//       background: red;
//       cursor: pointer;
//     }
//     body {
//       background-color: white;
//       text-align: center;
//       font-family: Arial, sans-serif;
//       -webkit-user-select: none;
//       -moz-user-select: none;
//       -ms-user-select: none;
//       user-select: none;
//     }
//     table {
//       margin: auto;
//       table-layout: fixed;
//       width: 320px;
//       border-spacing: 10px;
//     }
//   </style>
// </head>
// <body>
//   <h2>ESP32 Robot Control</h2>
//   <table id="mainTable">
//     <tr>
//       <td></td>
//       <td class="button" ontouchstart="sendButtonInput('MoveCar', '1')" ontouchend="sendButtonInput('MoveCar', '0')">&#8679;</td>
//       <td></td>
//     </tr>
//     <tr>
//       <td class="button" ontouchstart="sendButtonInput('MoveCar', '3')" ontouchend="sendButtonInput('MoveCar', '0')">&#8678;</td>
//       <td></td>
//       <td class="button" ontouchstart="sendButtonInput('MoveCar', '4')" ontouchend="sendButtonInput('MoveCar', '0')">&#8680;</td>
//     </tr>
//     <tr>
//       <td></td>
//       <td class="button" ontouchstart="sendButtonInput('MoveCar', '2')" ontouchend="sendButtonInput('MoveCar', '0')">&#8681;</td>
//       <td></td>
//     </tr>
//     <tr><td colspan="3">&nbsp;</td></tr>
//     <tr>
//       <td style="text-align:left"><b>Speed:</b></td>
//       <td colspan="2">
//         <div class="slidecontainer">
//           <input type="range" min="0" max="255" value="150" class="slider" id="Speed" oninput="sendButtonInput('Speed', this.value)">
//         </div>
//       </td>
//     </tr>
//     <tr>
//       <td style="text-align:left"><b>Light:</b></td>
//       <td colspan="2">
//         <div class="slidecontainer">
//           <input type="range" min="0" max="255" value="0" class="slider" id="Light" oninput="sendButtonInput('Light', this.value)">
//         </div>
//       </td>
//     </tr>
//   </table>

// <script>
//   function sendButtonInput(key, value) {
//     let url = "";
//     if (key === "MoveCar") {
//       switch (value) {
//         case "1": url = "/forward"; break;
//         case "2": url = "/backward"; break;
//         case "3": url = "/left"; break;
//         case "4": url = "/right"; break;
//         case "0": url = "/stop"; break;
//       }
//     } else if (key === "Speed") {
//       url = "/speed?value=" + value;
//     } else if (key === "Light") {
//       url = "/light?value=" + value;
//     }
//     if (url) {
//       fetch(url).catch(err => console.error("Request failed:", err));
//     }
//   }
// </script>

// </body>
// </html>
// )rawliteral";
