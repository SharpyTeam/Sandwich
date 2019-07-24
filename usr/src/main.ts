import sw from './sandwich';

let s = new sw.Sprite();

s.position.x = 15;
console.log(s.position);

let v1 = new sw.Vector2(new sw.Vector2(1, 212));
let v2 = new sw.Vector2(new sw.Vector2(123123));

function p() {
    console.log(v1, v2);
}

p();

v1.set(v2);
v2.set(123);

p();

v2.set(1, 1);
v1.normalize();

p();

sw.update = function (delta: number) {
    //console.log('FPS: ' + 1 / delta);
}