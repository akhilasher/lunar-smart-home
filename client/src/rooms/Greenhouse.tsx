interface GreenhouseProps {
  greenhouseTemp: number;
  greenhouseHum: number;
  greenhouseSoilHum: number;
}

export function Greenhouse({ greenhouseTemp, greenhouseHum, greenhouseSoilHum }: GreenhouseProps) {
  return (
    <div>
      <div>
        <h3>Temperature: {greenhouseTemp}°C</h3>
      </div>
      <div>
        <h3>Humidity: {greenhouseHum}%</h3>
      </div>
      <div>
        <h3>Soil Humidity: {greenhouseSoilHum}%</h3>
      </div>
    </div>
  );
}
