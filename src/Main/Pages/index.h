namespace Pages {
        const char indexHard[] PROGMEM = R"=====(
<!DOCTYPE html>
    <meta charset="UTF-8">
    <html>
        <style type="text/css">
            .button {
                background-color: #646464;
                border: none;
                border-radius: 5px;
                color: white;
                width: 40%;
                height: 72px;
                text-align: center;
                text-decoration: none;
                display: inline-block;
                font-size: 24px;
                cursor: pointer;
            }
            .button:hover {
                background-color: #575757;
            }
            .button:active {
                background-color: #4b4b4b;
            }

            .clear_button {
                background-color: #646464;
                border: none;
                color: white;
                width: 80%;
                border-radius: 5px;
                height: 100px;
                text-align: center;
                text-decoration: none;
                display: inline-block;
                font-size: 48px;
                cursor: pointer;
            }
            .clear_button:hover {
                background-color: #575757;
            }
            .clear_button:active {
                background-color: #4b4b4b;
            }
            
            #wifi_input_ssid {
                background-color: #646464;
                border: none;
                color: white;
                width: 40%;
                height: 70px;
                text-align: center;
                text-decoration: none;
                display: inline-block;
                font-size: 24px;
                border-radius: 5px;
            }

            #wifi_input_ssid::placeholder {
                color: whitesmoke;
                font-size: 24px;
                font-style: italic;
            }

            #wifi_input_psk {
                background-color: #646464;
                border: none;
                color: white;
                width: 40%;
                height: 70px;
                text-align: center;
                text-decoration: none;
                display: inline-block;
                font-size: 24px;
                border-radius: 5px;
            }

            #wifi_input_psk::placeholder {
                color: whitesmoke;
                font-size: 24px;
                font-style: italic;
            }

            #title_menu_text {
                font-size: 32px;
            }
        </style>
    <body onload="getDataStart()" style="background-color: #fffcf1 ">
        <center>
            <div>
                <div>
                    <p id="title_menu_text">??????????????????</p>
                    <!--<button class="button" onclick="sendGCODE('W1')">????????????????????</button>-->
                    <div style="width: 100%;">
                        <input type="text" value="" placeholder="SSID ????????..." id="wifi_input_ssid"></input>
                        <span/>
                        <br/>
                        <br/>
                        <input type="text" value="" placeholder="PSK ????????..." id="wifi_input_psk"></input>
                        <span/>
                        <br/>
                        <br/>
                        <button class="button" onclick="sendGCODE(`W102 ${document.getElementById('wifi_input_ssid').value} ${document.getElementById('wifi_input_psk').value}`)">??????????????</button>
                    </div>
                    <br/>
                </div>
            </div>
        </center>
    </body>
    <script>
        var currentTestTableLenght = 0;

        function sendGCODE(gcode) {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function() {
                if (this.readyState == 4 && this.status == 200) {
                    var data = JSON.parse(this.responseText);
                }
            };
            
            xhttp.open("GET", "scale_set?code=" + gcode, true);
            xhttp.send();
        }

        function clearTable() {
            document.getElementById("test_table_body").innerHTML = "";
            currentTestTableLenght = 0;
        }
        
        function getDataStart() {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function() {
                if (this.readyState == 4 && this.status == 200) {
                    var data = JSON.parse(this.responseText);

                    document.getElementById("wifi_input_ssid").value = data["wifi"]["ssid"];
                    document.getElementById("wifi_input_psk").value = data["wifi"]["psk"];
                }
            };

            xhttp.open("GET", "start_data", true);
            xhttp.send();
        }
    </script>
</html>
)=====";
    const char index[] PROGMEM = R"=====(
<!DOCTYPE html>
    <meta charset="UTF-8">
    <html>
        <style type="text/css">
            .button {
                background-color: #646464;
                border: none;
                border-radius: 5px;
                color: white;
                width: 40%;
                height: 150px;
                text-align: center;
                text-decoration: none;
                display: inline-block;
                font-size: 46px;
                cursor: pointer;
            }
            .button:hover {
                background-color: #575757;
            }
            .button:active {
                background-color: #4b4b4b;
            }

            .clear_button {
                background-color: #646464;
                border: none;
                color: white;
                width: 40%;
                border-radius: 5px;
                height: 250px;
                text-align: center;
                text-decoration: none;
                display: inline-block;
                font-size: 56px;
                cursor: pointer;
            }
            .clear_button:hover {
                background-color: #575757;
            }
            .clear_button:active {
                background-color: #4b4b4b;
            }
            
            #standart_weight_input {
                background-color: #646464;
                border: none;
                color: white;
                width: 40%;
                height: 148px;
                text-align: center;
                text-decoration: none;
                display: inline-block;
                font-size: 46px;
                border-radius: 5px;
            }

            #standart_weight_input::placeholder {
                color: whitesmoke;
                font-size: 24px;
                font-style: italic;
            }

            #coefficient_input {
                background-color: #646464;
                border: none;
                color: white;
                width: 40%;
                height: 148px;
                text-align: center;
                text-decoration: none;
                display: inline-block;
                font-size: 46px;
                border-radius: 5px;
            }

            #coefficient_input::placeholder {
                color: whitesmoke;
                font-size: 24px;
                font-style: italic;
            }
            
            #input_detail {
                
            }

            #input_summary {
                background-color: #646464;
                border: none;
                color: white;
                width: 40%;
                height: 150px;
                text-align: center;
                text-decoration: none;
                display: inline-block;
                font-size: 46px;
                line-height: 150px;
                border-radius: 5px;
                cursor: pointer;
            }

            #input_summary:hover {
                background-color: #575757;
            }
            #input_summary:active {
                background-color: #4b4b4b;
            }

            /* Chrome, Safari, Edge, Opera */
            input::-webkit-outer-spin-button,
            input::-webkit-inner-spin-button {
                -webkit-appearance: none;
                margin: 0;
            }

            /* Firefox */
            input[type=number] {
                -moz-appearance: textfield;
            }

            #weight_text {
                font-size: 81px;
                line-height: 10px;
            }

            #title_menu_text {
                font-size: 32px;
            }

            #prompt_text {
                background-color: #646464;
                border: none;
                color: white;
                width: 80%;
                height: fit-content;
                text-align: center;
                text-decoration: none;
                display: inline-block;
                font-size: 36px;
               
                border-radius: 5px;
                cursor: help;
            }

            #test_table {
                table-layout: fixed;
                width: 100%;
                border-collapse: collapse;
            }

            #test_table_head th:nth-child(1) {
                background-color: #363636;
                color: white;
                text-align: center;
                font-size: 32px;
                font-style: normal;

                /*border-top-left-radius: 10px;*/
                border-left: 3px solid rgb(44, 44, 44);
                border-right: 3px solid rgb(44, 44, 44);
                width: 20%;
            }
            #test_table_head th:nth-child(2) {
                background-color: #363636;
                color: white;
                text-align: center;
                font-size: 32px;
                font-style: normal;
                
                border-right: 3px solid rgb(44, 44, 44);
                width: 40%;
            }
            #test_table_head th:nth-child(3) {
                background-color: #363636;
                color: white;
                text-align: center;
                font-size: 32px;
                font-style: normal;
                
                /*border-top-right-radius: 10px;*/
                border-right: 3px solid rgb(44, 44, 44);
                width: 40%;
            }  

            #test_table_td {
                text-align: center;
                background-color: rgb(94, 94, 94);
                color: white;
                font-size: 24px;
                padding-top: 10px;
                padding-bottom: 10px;
                border-bottom: 3px inset rgb(73, 73, 73);
                border-right: 3px solid rgb(73, 73, 73);
                border-left: 3px solid rgb(73, 73, 73);
            }

        </style>
    <head>
        <script src="https://ajax.googleapis.com/ajax/lib/jquery/3.5.1/jquery.min.js"></script>
    </head>
    <body onload="getDataStart()" style="background-color: #fffcf1 ">
        <center>
            <div>
                <div>
                    <p id="weight_text">??????, <span id="units">????.</span></p>
                    <span id="weight" style="font-size: 256px; line-height: 128px;">NA</span>
                    <br/>
                    <br/>
                    <button class="clear_button" onclick="sendGCODE('W0')">????????????????</button>
                    <button class="clear_button" onclick="if (currentTestTableLenght != 8) {sendGCODE('W11');}">????????????????</button>
                </div>
                <div>
                    <p id="title_menu_text">?????????????? ??????????????????</p>
                    <button class="button" onclick="sendGCODE('W3 0')">????????????</button>
                    <button class="button" onclick="sendGCODE('W3 1')">????????????????????</button>
                </div>
                <br/>
                <div>
                    <details id="input_detail">
                        <summary id="input_summary">??????????????</summary>
                        <br/>
                        <br/>
                        <div style="width: 100%;">
                            <br/>
                            <button class="button" onclick="sendGCODE('W10')">????????????????</button>
                            <br/>
                            <br/>
                            <br/>
                            <span/>
                            <table id="test_table">
                                <thead id="test_table_head">
                                    <th id="test_table_th" scope="col">????????????</th>
                                    <th id="test_table_th" scope="col">??????</th>
                                    <th id="test_table_th" scope="col">????????????</th>
                                </thead>
                                <tbody id="test_table_body">
                                    <tr>
                                        <td id="test_table_td">0</td>
                                        <td id="test_table_td">200</td>
                                        <td id="test_table_td">20</td>
                                    </tr>
                                    <tr>
                                        <td id="test_table_td">1</td>
                                        <td id="test_table_td">200</td>
                                        <td id="test_table_td">20</td>
                                    </tr>
                                </tbody>
                            </table>
                        </div>
                    </details>
                </div>
                <div>
                    <p id="title_menu_text">??????????????????</p>
                    <!--<button class="button" onclick="sendGCODE('W1')">????????????????????</button>-->
                    <details id="input_detail">
                        <summary id="input_summary">????????????????????</summary>
                        <br/>
                        <br/>
                        <div style="width: 100%;">
                            <input type="number" value="0" placeholder="?????????????? ??????..." id="standart_weight_input"></input>
                            <span/>
                            <button class="button" onclick="sendGCODE('W1 ' +  + document.getElementById('standart_weight_input').value)">??????????????</button>
                            <p id="prompt_text"> 
                                ???????????????????? ???? ???????????????????? ????????????????????.
                                <br/>
                                <br/>
                                1. ???????????? ?????? ???? ???????? ??????????.
                                <br/>
                                2. ???????????????? ?????????? ?? ???????????????????????????? ???????? ??????????.
                                <br/>
                                3. ???????????? ???? ???????????? ??????????????.
                                <br/>
                                4. ?? ?????????????? 10 ???????????? ???????????????? ???????? ?? ???????????? ???????????? ???? ???????? ?? ?????????????????? ???????????????????? ???????????????????? (???? ?????????????? ?????????? ?? ???? ?????????? ?? ?????? ??????????).
                                <br/>
                                <br/>
                                P.S. ?????? ???? ???????????????????? ?????????????? ???????????????? ?????????????????????????????????? ???? ??????????????????????????.
                            </p>
                        </div>
                    </details>
                    <br/>
                    <details id="input_detail">
                        <summary id="input_summary">??????????????????????</summary>
                        <br/>
                        <br/>
                        <div style="width: 100%;">
                            <input type="number" value="0" placeholder="?????????? ????????????????????..." id="coefficient_input"></input>
                            <span/>
                            <button class="button" onclick="sendGCODE('W2 ' + document.getElementById('coefficient_input').value)">??????????????</button>
                        </div>
                    </details>
                </div>
            </div>
        </center>
    </body>
    <script>
        var currentTestTableLenght = 0;
        var wasServerAwake = false;

        function sendGCODE(gcode) {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function() {
                if (this.readyState == 4 && this.status == 200) {
                    var data = JSON.parse(this.responseText);

                    document.getElementById("coefficient_input").value = data["scales"]["scaleCalibration"];
                    Update(data);
                }
            };
            
            xhttp.open("GET", "scale_set?code=" + gcode, true);
            xhttp.send();
        }

        function clearTable() {
            document.getElementById("test_table_body").innerHTML = "";
            currentTestTableLenght = 0;
        }
        
        var updateID = 0;

        function getDataStart() {
            wasServerAwake = true;
            
        }

        updateID = window.setInterval(function() { if (wasServerAwake) { getDataUpdate(); } }, 1000);
        function getDataUpdate() {
            var xhttp = new XMLHttpRequest();

            xhttp.onreadystatechange = function() {
                if (this.readyState == 4 && this.status == 200) {
                    var data = JSON.parse(this.responseText);
                    Update(data);
                    document.getElementById("coefficient_input").value = data["scales"]["scaleCalibration"];
                }
            };

            xhttp.open("GET", "update_data", true);
            xhttp.send();
        }

        function Update(json) {
            setWeight(json["scales"]["weight"], json["scales"]["isGr_Mode"]);
            setTestTable(json);
        }

        function setTestTable(data) {
            clearTable();

            var table = data["table"];
            currentTestTableLenght = table["length"];
            for (let i = 0; i < table["length"]; i++) {
                document.getElementById("test_table_body").innerHTML += `
                    <tr>
                        <td id="test_table_td">${i}</td>
                        <td id="test_table_td">${table[i]["weight"]}</td>
                        <td id="test_table_td">${table[i]["lenght"]}</td>
                    </tr>
                `;
            }
        }

        function setWeight(weight, mode) {
            document.getElementById("units").innerHTML = `${(mode) ? " ????." : " ????."}`
            document.getElementById("weight").innerHTML = (mode) ?  Math.round(weight * 0.001) : weight;
        }
    </script>
</html>
)=====";
};