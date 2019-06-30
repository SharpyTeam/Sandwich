declare namespace sw {
    class Vector2 {
        x: number;
        y: number;

        constructor();
        constructor(scalar: number);
        constructor(x: number, y: number);
        constructor(other: Vector2);

        set(scalar: number): Vector2;
        set(x: number, y: number): Vector2;
        set(other: Vector2): Vector2;

        length(): number;
        lengthSquared(): number;

        normalized(): Vector2;
        normalize(): Vector2;

        distance(to: Vector2): number;
        distance(tox: number, toy: number): number;

        distanceSquared(to: Vector2): number;
        distanceSquared(tox: number, toy: number): number;

        angle(to: Vector2): number;
        angle(tox: number, toy: number): number;

        dot(to: Vector2): number;
        dot(tox: number, toy: number): number;

        perpendicular(to: Vector2): Vector2;
        perpendicular(tox: number, toy: number): Vector2;

        lerp(to: Vector2, t: number): Vector2;
        lerp(tox: number, toy: number, t: number): Vector2;
    }

    var vvv: Vector2;
}

export default sw;