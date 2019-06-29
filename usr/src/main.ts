import sw from './sandwich';

console.log(sw.Vector2);

for (let i = 0; i < 100000000000; ++i) {
    new sw.Vector2();
}

while (true) {}