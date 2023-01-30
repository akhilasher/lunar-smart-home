import { ThemeProvider, createTheme } from "@mui/material/styles";
import { deepOrange } from "@mui/material/colors";

import React from "react";
import ReactDOM from "react-dom/client";
import App from "./App";
import "./index.css";

ReactDOM.createRoot(document.getElementById("root") as HTMLElement).render(
  <React.StrictMode>
    <ThemeProvider theme={createTheme({ palette: { mode: "dark", primary: deepOrange } })}>
      <App />
    </ThemeProvider>
  </React.StrictMode>
);
