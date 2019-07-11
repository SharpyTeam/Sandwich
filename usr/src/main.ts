import sw from './sandwich';

console.log("JS: " + sw.vvv.x);
console.log("JS: " + sw.vvv.y);
console.log("JS: " + sw.vvv.z);
console.log("JS: Changing vector...")
sw.vvv.x = 11;
sw.vvv.y = 22;
sw.vvv.z = 33;
console.log("JS: Vector was changed.");

sw.update = function (delta: number) {
    console.log("FPS: " + 1 / delta);
}