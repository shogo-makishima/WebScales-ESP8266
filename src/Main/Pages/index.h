namespace Pages {
    const char index[] PROGMEM = R"=====(
<!DOCTYPE html>
    <meta charset="UTF-8">
    <html>
        <style type="text/css">
            .button {
                background-color: #646464;
                border: none;
                color: white;
                width: 40%;
                height: 52px;
                text-align: center;
                text-decoration: none;
                display: inline-block;
                font-size: 16px;
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
                width: 75%;
                height: 100px;
                text-align: center;
                text-decoration: none;
                display: inline-block;
                font-size: 36pt;
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
                height: 50px;
                text-align: center;
                text-decoration: none;
                display: inline-block;
                font-size: 16px;
            }

            #standart_weight_input::placeholder {
                color: whitesmoke;
                font-size: 16px;
                font-style: italic;
            }

            #coefficient_input {
                background-color: #646464;
                border: none;
                color: white;
                width: 40%;
                height: 50px;
                text-align: center;
                text-decoration: none;
                display: inline-block;
                font-size: 16px;
            }

            #coefficient_input::placeholder {
                color: whitesmoke;
                font-size: 16px;
                font-style: italic;
            }
            
            #input_detail {
            }

            #input_summary {
                background-color: #646464;
                border: none;
                color: white;
                width: 40%;
                height: 52px;
                text-align: center;
                text-decoration: none;
                display: inline-block;
                font-size: 24px;
                line-height: 52px;
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
                font-size: 48pt;
            }
        </style>
    <body onload="getDataStart()" style="background-color: #fffcf1 ">
        <center>
            <div>
                <div>
                    <p id="weight_text">Вес: <span id="weight">NA</span><span id="units"> гр.</span></span></p>
                    <button class="clear_button" onclick="sendGCODE('W0')">Обнулить</button>
                </div>
                <div>
                    <h2>Единицы измерения</h2>
                    <button class="button" onclick="sendGCODE('W3\s0')">Граммы</button>
                    <button class="button" onclick="sendGCODE('W3 1')">Килограммы</button>
                </div>
                <div>
                    <h2>Настройки</h2>
                    <br/>
                    <!--<button class="button" onclick="sendGCODE('W1')">Калибровка</button>-->
                    <details id="input_detail">
                        <summary id="input_summary">Калибровка</summary>
                        <br/>
                        <br/>
                        <input type="number" value="0" placeholder="Базовый вес..." id="standart_weight_input"></input>
                        <span/>
                        <button class="button" onclick="sendGCODE('W1 ' +  + document.getElementById('standart_weight_input').value)">Принять</button>
                    </details>
                    <br/>
                    <details id="input_detail">
                        <summary id="input_summary">Коэффициент</summary>
                        <br/>
                        <br/>
                        <input type="number" value="0" placeholder="Введите новый коэффицент..." id="coefficient_input"></input>
                        <span/>
                        <button class="button" onclick="sendGCODE('W2 ' + document.getElementById('coefficient_input').value)">Принять</button>
                    </details>
                </div>
            </div>
        </center>
    </body>
    <script>
        function sendGCODE(gcode) {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function() {
                if (this.readyState == 4 && this.status == 200) {
                    var data = JSON.parse(this.responseText);
                    Update(data);
                }
            };
            
            
            xhttp.open("GET", "scale_set?code=" + gcode, true);
            xhttp.send();
        }
        
        function getDataStart() {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function() {
                if (this.readyState == 4 && this.status == 200) {
                    var data = JSON.parse(this.responseText);
                    
                    document.getElementById("coefficient_input").value = data["scales"]["scaleCalibration"];
                    document.getElementById("standart_weight_input").value = data["scales"]["weightStandard"];
                    Update(data);
                }
            };

            xhttp.open("GET", "start_data", true);
            xhttp.send();
        }

        setInterval(function() { getDataUpdate(); }, 500); 
        function getDataUpdate() {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function() {
                if (this.readyState == 4 && this.status == 200) {
                    var data = JSON.parse(this.responseText);
                    Update(data);
                }
            };

            xhttp.open("GET", "update_data", true);
            xhttp.send();
        }

        function Update(json) {
            setWeight(json["scales"]["weight"], json["scales"]["isGr_Mode"]);
        }

        function setWeight(weight, mode) {
            if (mode == true) {
                document.getElementById("weight").innerHTML = weight * 1000;
                document.getElementById("units").innerHTML = " кг.";
            } else {
                document.getElementById("weight").innerHTML = weight;
                document.getElementById("units").innerHTML = " гр.";
            }
        }
    </script>
</html>
)=====";
};