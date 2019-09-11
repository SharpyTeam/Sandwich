import sw from './sandwich';

sw.update = function (delta: number) {
    console.log("Greetings from TypeScript!");
    let v1 = new sw.Vector2(1, 3);
    let v2 = new sw.Vector2(-3, 1);
    console.log("Angle between", v1, "and", v2, "is", v1.angle(v2), "rad");
    //console.log('FPS: ' + 1 / delta);
    sw.update = null;
}