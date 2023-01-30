import serveHandler from "serve-handler";
import httpProxy from "http-proxy";
import http from "http";

const proxy = httpProxy.createProxyServer();
const server = http.createServer((request, response) => {
  console.log(request.url);
  if (request.url === "/_ws") {
    console.log("Proxying websocket");
    proxy.web(request, response, { target: "ws://localhost:12345", ws: true });
  } else serveHandler(request, response, { public: "dist" });
});

server.on("upgrade", (req, socket, head) => {
  proxy.ws(req, socket, head, { target: "ws://localhost:12345" });
});

server.listen(3000, async () => {
  console.log("Running at http://localhost:3000");
});
