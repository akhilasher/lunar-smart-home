import Slider from "@mui/material/Slider";
import Switch from "@mui/material/Switch";

interface BedroomProps {
  ws: WebSocket | null;

  bedroomFan: boolean;
  bedroomFanAuto: boolean;
  bedroomTemp: number;
  bedroomHum: number;

  requiredBedroomTemp: number;
  requiredBedroomHumidity: number;

  setBedroomFan: (value: boolean) => void;
  setBedroomFanAuto: (value: boolean) => void;
  setRequiredBedroomTemp: (value: number) => void;
  setRequiredBedroomHumidity: (value: number) => void;
}

export function Bedroom({
  ws,

  bedroomFan,
  bedroomFanAuto,
  bedroomTemp,
  bedroomHum,
  requiredBedroomTemp,

  setBedroomFan,
  setBedroomFanAuto,
  setRequiredBedroomTemp
}: BedroomProps) {
  return (
    <div>
      <div>
        <h3>Temperature: {bedroomTemp}°C</h3>
      </div>
      <div>
        <h3>Humidity: {bedroomHum}%</h3>
      </div>
      <div>
        <h3>
          Fan Auto:
          <Switch
            checked={bedroomFanAuto}
            onChange={e => {
              ws?.send(e.target.checked ? "settings,bedroom_fan_auto=true" : "settings,bedroom_fan_auto=false");
              setBedroomFanAuto(e.target.checked);
            }}
            color="primary"
            name="checkedB"
            inputProps={{ "aria-label": "primary checkbox" }}
          />
        </h3>
      </div>
      <div>
        <h3>
          Fan:
          <Switch
            checked={bedroomFan}
            disabled={bedroomFanAuto}
            onChange={e => {
              ws?.send(e.target.checked ? "bedroom_fan_on" : "bedroom_fan_off");
              setBedroomFan(e.target.checked);
            }}
            color="primary"
            name="checkedB"
            inputProps={{ "aria-label": "primary checkbox" }}
          />
        </h3>
      </div>
      <div>
        <h3>
          Preferred temperature:
          <Slider
            value={requiredBedroomTemp}
            onChange={(e, value) => {
              ws?.send(`settings,required_bedroom_temp=${value}`);
              setRequiredBedroomTemp(value as number);
            }}
            valueLabelDisplay="auto"
            step={1}
            marks
            min={15}
            max={30}
          />
        </h3>
      </div>
    </div>
  );
}
