import sw from './sandwich';

sw.update = function (delta: number) {
    try {
        // @ts-ignore
        let a = new A(new Vector2(1), new Vector2(2, 3));
        let vv = a.pos;
        vv.x = 5555;
        let gg = a.v;
        gg.x = 5555;
        console.log(a.v.x, a.pos.x);
    } catch (e) {
        console.log("lol" + e);
    }
    //console.log('FPS: ' + 1 / delta);
    sw.update = null;
}