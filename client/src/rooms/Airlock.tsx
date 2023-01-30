interface AirlockProps {
  airlockIn: boolean;
  airlockOut: boolean;
}

export function Airlock({ airlockIn, airlockOut }: AirlockProps) {
  return (
    <div>
      <div>
        <h3>Airlock In: {airlockIn ? "Open" : "Closed"}</h3>
      </div>
      <div>
        <h3>Airlock Out: {airlockOut ? "Open" : "Closed"}</h3>
      </div>
    </div>
  );
}
