import sw from './sandwich';

let sb: sw.SpriteBatch;
let t: sw.Texture;
let m: sw.math.Matrix4;

sw.init = function () {
    sb = new sw.SpriteBatch();
    m = new sw.math.Matrix4();
}

let elapsed = 0;
sw.update = function (delta: number) {
    m.setOrtho2D(-sw.Screen.width / 2, sw.Screen.width / 2, -sw.Screen.height / 2, sw.Screen.height / 2);
    sb.setProjectionMatrix(m);

    //console.log("Greetings from TypeScript!");
    //let v1 = new sw.Vector2(1, 3);
    //let v2 = new sw.Vector2(-3, 1);
    //console.log("Angle between", v1, "and", v2, "is", v1.angle(v2), "rad");
    //console.log('FPS: ' + 1 / delta);
    //sw.update = null;

    let data = new sw.TextureData(100, 100);
    for (let x = 0; x < 100; ++x) {
        for (let y = 0; y < 100; ++y) {
            data.setPixel(x, y, (Math.sin(2 * Math.PI / 100 * (x * 101 + y - elapsed * 100)) + 1) * 0.5, (Math.sin(2 * Math.PI / 100 * (x * 75 - y + elapsed * 1000)) + 1) * 0.5, (Math.sin(2 * Math.PI / 100 * (x * 80 + elapsed * 1300)) + 1) * 0.5, 1);
        }
    }
    t = sw.Texture.create(data);

    sb.begin();
    sb.draw(t, 0, 100 * Math.sin(elapsed), 0, 0.5, 0.5, 1, 1, false, false);
    sb.end();
    elapsed += delta;
    if (elapsed > 3 && elapsed < 6) {
        elapsed = 6;
        let resolutions = sw.Screen.getSupportedFullscreenResolutions();
        let resolution = resolutions[resolutions.length - 1];
        sw.Screen.setResolution(resolution.width, resolution.height, sw.Screen.ScreenMode.FULLSCREEN, resolution.refreshRate);
    }
}