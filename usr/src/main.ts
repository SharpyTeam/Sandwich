import sw from './sandwich';

let sb: sw.SpriteBatch;
let t: sw.Texture;

sw.init = function () {
    sb = new sw.SpriteBatch();
    let m = new sw.Matrix4();
    m.setOrtho2D(-320, 320, -240, 240);
    sb.setProjectionMatrix(m);
    let data = new sw.TextureData(100, 100);
    for (let x = 0; x < 100; ++x) {
        for (let y = 0; y < 100; ++y) {
            data.setPixel(x, y, Math.sin(x / 50), Math.cos(y / 10), 0, 1);
        }
    }
    t = sw.Texture.create(data);
}

let elapsed = 0;
sw.update = function (delta: number) {
    //console.log("Greetings from TypeScript!");
    //let v1 = new sw.Vector2(1, 3);
    //let v2 = new sw.Vector2(-3, 1);
    //console.log("Angle between", v1, "and", v2, "is", v1.angle(v2), "rad");
    //console.log('FPS: ' + 1 / delta);
    //sw.update = null;
    sb.begin();
    sb.draw(t, 0, 100 * Math.sin(elapsed), 0, 0.5, 0.5, 1, 1, false, false);
    sb.end();
    elapsed += delta;
}