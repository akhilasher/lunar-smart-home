import qr from "qrcode-terminal";

qr.setErrorLevel("Q");

const url = process.argv[2];
qr.generate(url, qrcode => {
  console.log(qrcode);
});
