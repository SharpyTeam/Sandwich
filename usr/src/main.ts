import sw from './sandwich';

let i = 0;
sw.update = function (delta: number) {
    // @ts-ignore
    // let z = new Z();
    // console.log(z.x, z.y, z.o);
    // z.x = 3;
    // z.y = 4;
    //z.o = 15;
    // z.op += 1;
    // z[666] = 1;
    // console.log(z.v);
    // for (let i = 0; i < z.v.length; ++i) {
    //     z.v[i] = i * 2;
    // }
    // console.log(z.v);
    // @ts-ignore
    // console.log(Vector2.staticFunction(), Vector2.staticVar);
    // @ts-ignore
    let a = new Vector2(-3, -4);
    console.log(a.length());
    a.add(1);
    console.log(a.x, a.y);
    console.log(a.length());
    // @ts-ignore
    let b = Vector2.add(a, a);
    console.log(b.x, b.y);
    // console.log(z, z.length(), z.op, z[12], z[54], z.angle(new Vector2(-3, -4)), z.angle(-6, -8));
    //console.log('FPS: ' + 1 / delta);
    sw.update = null;
}