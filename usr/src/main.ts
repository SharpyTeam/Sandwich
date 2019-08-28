import sw from './sandwich';

sw.update = function (delta: number) {
    //console.log('FPS: ' + 1 / delta);
    // @ts-ignore
    console.log(sw.a.x);
    // @ts-ignore
    console.log(sw.a[0].x);
    // @ts-ignore
    console.log(sw.a[1].x);
    // @ts-ignore
    sw.a[0] = sw.a[1];
    // @ts-ignore
    console.log(sw.a[0].x);
    // @ts-ignore
    console.log(sw.a[1].x);
    sw.update = null;
}