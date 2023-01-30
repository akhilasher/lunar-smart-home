import { ReactNode } from "react";

export function Room({ room, children }: { room: string; children: ReactNode }) {
  return (
    <details>
      <summary className="room-name">{room}</summary>
      <div className="room">{children}</div>
    </details>
  );
}
