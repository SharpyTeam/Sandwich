import sw from './sandwich';

let i = 0;
sw.update = function (delta: number) {
    // @ts-ignore
    let z = new Vector2(1);
    console.log(z.x, z.y, z.o);
    z.x = 3;
    z.y = 4;
    // @ts-ignore
    console.log(z.length(), z.angle(new Vector2(-3, -4)), z.angle(-6, -8));
    //console.log('FPS: ' + 1 / delta);
    sw.update = null;
}