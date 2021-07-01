namespace Pages {
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
            
            #standart_weight_input {
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
                height: 70px;
                text-align: center;
                text-decoration: none;
                display: inline-block;
                font-size: 24px;
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
                height: 72px;
                text-align: center;
                text-decoration: none;
                display: inline-block;
                font-size: 24px;
                line-height: 72px;
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
                font-size: 24px;
               
                border-radius: 5px;
                cursor: help;
            }
        </style>
    <body onload="getDataStart()" style="background-color: #fffcf1 ">
        <center>
            <div>
                <div>
                    <p id="weight_text">Вес: <span id="weight">NA</span></p>
                    <button class="clear_button" onclick="sendGCODE('W0')">Обнулить</button>
                </div>
                <div>
                    <p id="title_menu_text">Единицы измерения</p>
                    <button class="button" onclick="sendGCODE('W3 0')">Граммы</button>
                    <button class="button" onclick="sendGCODE('W3 1')">Килограммы</button>
                </div>
                <div>
                    <p id="title_menu_text">Настройки</p>
                    <!--<button class="button" onclick="sendGCODE('W1')">Калибровка</button>-->
                    <details id="input_detail">
                        <summary id="input_summary">Калибровка</summary>
                        <br/>
                        <br/>
                        <div style="width: 100%;">
                            <input type="number" value="0" placeholder="Базовый вес..." id="standart_weight_input"></input>
                            <span/>
                            <button class="button" onclick="sendGCODE('W1 ' +  + document.getElementById('standart_weight_input').value)">Принять</button>
                            <p id="prompt_text"> 
                                Инструкция по выполнению калибровки.
                                <br/>
                                <br/>
                                1. Убрать все из чаши весов.
                                <br/>
                                2. Написать массу в соответсвующее поле ввода.
                                <br/>
                                3. Нажать на кнопку принять.
                                <br/>
                                4. В течении 10 секунд положить груз с данной массой на весы и дождаться результата калибровки (не касаясь весов и не кладя в них грузы).
                                <br/>
                                <br/>
                                P.S. При не соблюдении порядка действий работоспособность не гарантирована.
                            </p>
                        </div>
                    </details>
                    <br/>
                    <details id="input_detail">
                        <summary id="input_summary">Коэффициент</summary>
                        <br/>
                        <br/>
                        <div style="width: 100%;">
                            <input type="number" value="0" placeholder="Новый коэффицент..." id="coefficient_input"></input>
                            <span/>
                            <button class="button" onclick="sendGCODE('W2 ' + document.getElementById('coefficient_input').value)">Принять</button>
                        </div>
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

                    document.getElementById("coefficient_input").value = data["scales"]["scaleCalibration"];
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
            document.getElementById("weight").innerHTML = (mode) ?  Math.round(weight * 0.001) + " кг." : weight + " гр.";
        }
    </script>
</html>
)=====";
};