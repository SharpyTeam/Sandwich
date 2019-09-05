import sw from './sandwich';

sw.update = function (delta: number) {
    try {
        // @ts-ignore
        let a = new A();
        let v1 = a.v1;
        let v2 = a.v2;
        let v3 = a.v3;
        v1.x = 777;
        v2.x = 777;
        v3.x = 777;
        console.log(v1.x, a.v1.x);
        console.log(v2.x, a.v2.x);
        console.log(v3.x, a.v3.x);

        // @ts-ignore
        console.log(new Vector2(45, 54).y);
    } catch (e) {
        console.log("lol" + e);
    }
    //console.log('FPS: ' + 1 / delta);
    sw.update = null;
}