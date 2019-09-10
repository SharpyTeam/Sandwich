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
    console.log("Greetings from TypeScript!");
    console.log("From JS: creating Vector2");
    let a = new sw.Vector2(-3, -4);
    console.log("From JS: calling Vector2::length function");
    console.log("From JS: " + a.length());
    console.log("From JS: calling 'add' on Vector2");
    a.add(1);
    console.log("From JS: " + a.x, a.y);
    console.log("From JS: " + a.length());
    console.log("From JS: creating Vector2 by calling static function 'add' on Vector2");
    let b = sw.Vector2.add(a, a);
    console.log("From JS: " + b.x, b.y);
    // console.log(z, z.length(), z.op, z[12], z[54], z.angle(new Vector2(-3, -4)), z.angle(-6, -8));
    //console.log('FPS: ' + 1 / delta);
    sw.update = null;
}