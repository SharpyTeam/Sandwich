import sw from './sandwich';

let s = new sw.Sprite();

sw.update = function (delta: number) {
    console.log(s.scale.x);
}