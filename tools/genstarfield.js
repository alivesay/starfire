const NUMSTARS = 110;
const WIDTH = 128;
const HEIGHT = 64;

function d2h(d) {
    var s = (+d).toString(16);
    if(s.length < 2) {
        s = '0' + s;
    }
    return '0x' + s;
}

let output = "";
let values = "";

for (let i = 0; i < NUMSTARS; i++) {
  let x = Math.floor(Math.random() * WIDTH - 1) + 1;
  let y = Math.floor(Math.random() * HEIGHT - 1) + 1;

  values += d2h(x) + ", " + d2h(y) + ", ";
}

values = values.slice(0, -2).match(/.{1,78}/g);

output = "const uint8_t PROGMEM starfield[] = \n{\n" + values.join("\n") + "\n};\n";

console.log(output);
