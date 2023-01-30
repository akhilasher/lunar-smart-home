import "./App.css";

import { useEffect, useRef, useState } from "react";
import { Spinner } from "./components/Spinner";

import "highlight.js/styles/vs2015.css";
import hljs from "highlight.js/lib/core";
import json from "highlight.js/lib/languages/json";

import { Bedroom } from "./rooms/Bedroom";
import { Room } from "./components/Room";
import { Kitchen } from "./rooms/Kitchen";
import { Greenhouse } from "./rooms/Greenhouse";
import { Airlock } from "./rooms/Airlock";

hljs.registerLanguage("json", json);

interface State {
  // bedroom
  bedroom_fan: boolean;
  bedroom_hum: number;
  bedroom_temp: number;

  // kitchen
  kitchen_light: boolean;
  kitchen_hum: number;
  kitchen_temp: number;
  kitchen_gas_level: number;

  // greenhouse
  greenhouse_hum: number;
  greenhouse_temp: number;
  greenhouse_soil_hum: number;

  // airlock
  airlock_in: boolean;
  airlock_out: boolean;

  // settings
  settings: {
    bedroom_fan_auto: boolean;
    required_bedroom_hum: number;
    required_bedroom_temp: number;
  };
}

function App() {
  const [ws, setWs] = useState<WebSocket | null>(null);

  // bedroom
  const [bedroomFan, setBedroomFan] = useState<boolean>(false);
  const [bedroomFanAuto, setBedroomFanAuto] = useState<boolean>(false);
  const [bedroomTemp, setBedroomTemp] = useState<number>(0);
  const [bedroomHum, setBedroomHum] = useState<number>(0);

  // kitchen
  const [kitchenLight, setKitchenLight] = useState<boolean>(false);
  const [kitchenTemp, setKitchenTemp] = useState<number>(0);
  const [kitchenHum, setKitchenHum] = useState<number>(0);
  const [kitchenGasLevel, setKitchenGasLevel] = useState<number>(0);

  // greenhouse
  const [greenhouseTemp, setGreenhouseTemp] = useState<number>(0);
  const [greenhouseHum, setGreenhouseHum] = useState<number>(0);
  const [greenhouseSoilHum, setGreenhouseSoilHum] = useState<number>(0);

  // airlock
  const [airlockIn, setAirlockIn] = useState<boolean>(false);
  const [airlockOut, setAirlockOut] = useState<boolean>(false);

  // settings
  const [requiredBedroomTemp, setRequiredBedroomTemp] = useState<number>(20);
  const [requiredBedroomHumidity, setRequiredBedroomHumidity] = useState<number>(50);

  const logs = useRef<HTMLDivElement>(null);

  // initiate websocket
  useEffect(() => {
    // @ts-ignore
    if (window.__ws) return;
    // @ts-ignore
    window.__ws = true;
    const ws = new WebSocket(`${location.protocol === "https:" ? "wss" : "ws"}://${location.host}/_ws`);
    ws.onopen = () => {
      console.log("connected");
      setWs(ws);
    };

    ws.onmessage = e => {
      // parse state
      const data: State = JSON.parse(e.data);

      // update state
      setBedroomTemp(data.bedroom_temp);
      setBedroomHum(data.bedroom_hum);
      setBedroomFan(data.bedroom_fan);
      setBedroomFanAuto(data.settings.bedroom_fan_auto);
      setKitchenLight(data.kitchen_light);
      setKitchenTemp(data.kitchen_temp);
      setKitchenHum(data.kitchen_hum);
      setKitchenGasLevel(data.kitchen_gas_level);
      setGreenhouseTemp(data.greenhouse_temp);
      setGreenhouseHum(data.greenhouse_hum);
      setGreenhouseSoilHum(data.greenhouse_soil_hum);
      setAirlockIn(data.airlock_in);
      setAirlockOut(data.airlock_out);
      setRequiredBedroomHumidity(data.settings.required_bedroom_hum);
      setRequiredBedroomTemp(data.settings.required_bedroom_temp);

      // log
      if (logs.current) {
        const log = document.createElement("div");
        log.innerHTML = hljs.highlight(e.data, { language: "json" }).value;
        logs.current.append(log);
        if (logs.current.childElementCount > 100) logs.current.removeChild(logs.current.firstChild!);
      }
    };

    ws.onclose = () => {
      console.log("disconnected");
    };
  }, [logs]);

  return (
    <>
      <header className="header">Dashboard</header>
      <main className="main">
        {ws ? (
          <>
            <Room room="Bedroom">
              <Bedroom
                ws={ws}
                bedroomFan={bedroomFan}
                bedroomFanAuto={bedroomFanAuto}
                bedroomTemp={bedroomTemp}
                bedroomHum={bedroomHum}
                setBedroomFan={setBedroomFan}
                setBedroomFanAuto={setBedroomFanAuto}
                requiredBedroomTemp={requiredBedroomTemp}
                requiredBedroomHumidity={requiredBedroomHumidity}
                setRequiredBedroomTemp={setRequiredBedroomTemp}
                setRequiredBedroomHumidity={setRequiredBedroomHumidity}
              />
            </Room>
            <Room room="Kitchen">
              <Kitchen
                ws={ws}
                kitchenGasLevel={kitchenGasLevel}
                kitchenLight={kitchenLight}
                kitchenTemp={kitchenTemp}
                kitchenHum={kitchenHum}
                setKitchenLight={setKitchenLight}
              />
            </Room>
            <Room room="Greenhouse">
              <Greenhouse
                greenhouseTemp={greenhouseTemp}
                greenhouseHum={greenhouseHum}
                greenhouseSoilHum={greenhouseSoilHum}
              />
            </Room>
            <Room room="Airlock">
              <Airlock airlockIn={airlockIn} airlockOut={airlockOut} />
            </Room>
          </>
        ) : (
          <Spinner />
        )}
        <div ref={logs} className="logs"></div>
      </main>
    </>
  );
}

export default App;
