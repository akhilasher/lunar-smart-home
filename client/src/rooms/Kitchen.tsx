import Switch from "@mui/material/Switch";

interface KitchenProps {
  ws: WebSocket | null;

  kitchenGasLevel: number;
  kitchenLight: boolean;
  kitchenTemp: number;
  kitchenHum: number;

  setKitchenLight: (value: boolean) => void;
}

export function Kitchen({
  ws,

  kitchenGasLevel,
  kitchenLight,
  kitchenTemp,
  kitchenHum,

  setKitchenLight
}: KitchenProps) {
  return (
    <div>
      <div>
        <h3>Temperature: {kitchenTemp}°C</h3>
      </div>
      <div>
        <h3>Humidity: {kitchenHum}%</h3>
      </div>
      <div>
        <h3>Gas Level: {kitchenGasLevel}%</h3>
      </div>
      <div>
        <h3>
          Light:{" "}
          <Switch
            checked={kitchenLight}
            onChange={e => {
              ws?.send(e.target.checked ? "kitchen_light_on" : "kitchen_light_off");
              setKitchenLight(e.target.checked);
            }}
            color="primary"
            name="checkedB"
            inputProps={{ "aria-label": "primary checkbox" }}
          />
        </h3>
      </div>
    </div>
  );
}
