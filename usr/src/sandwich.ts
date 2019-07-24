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

        perpendicular(): Vector2;

        lerp(to: Vector2, t: number): Vector2;
        lerp(tox: number, toy: number, t: number): Vector2;
    }

    class Vector3 {
        x: number;
        y: number;
        z: number;

        constructor();
        constructor(scalar: number);
        constructor(x: number, y: number, z: number);
        constructor(other: Vector2);

        set(scalar: number): Vector2;
        set(x: number, y: number, z: number): Vector2;
        set(other: Vector2): Vector2;

        length(): number;
        lengthSquared(): number;

        normalized(): Vector2;
        normalize(): Vector2;

        distance(to: Vector2): number;
        distance(tox: number, toy: number, toz: number): number;

        distanceSquared(to: Vector2): number;
        distanceSquared(tox: number, toy: number, toz: number): number;

        angle(to: Vector2): number;
        angle(tox: number, toy: number, toz: number): number;

        dot(to: Vector2): number;
        dot(tox: number, toy: number, toz: number): number;

        perpendicular(): Vector2;

        lerp(to: Vector2, t: number): Vector2;
        lerp(tox: number, toy: number, toz: number, t: number): Vector2;
    }

    class Vector4 {
        x: number;
        y: number;
        z: number;
        w: number;

        constructor();
        constructor(scalar: number);
        constructor(x: number, y: number, z: number, w: number);
        constructor(other: Vector2);

        set(scalar: number): Vector4;
        set(x: number, y: number, z: number, w: number): Vector4;
        set(other: Vector4): Vector4;

        length(): number;
        lengthSquared(): number;

        normalized(): Vector4;
        normalize(): Vector4;

        distance(to: Vector4): number;
        distance(tox: number, toy: number, toz: number, tow: number): number;

        distanceSquared(to: Vector4): number;
        distanceSquared(tox: number, toy: number, toz: number, tow: number): number;

        angle(to: Vector4): number;
        angle(tox: number, toy: number, toz: number, tow: number): number;

        dot(to: Vector4): number;
        dot(tox: number, toy: number, toz: number, tow: number): number;

        perpendicular(to: Vector4): Vector4;
        perpendicular(tox: number, toy: number, toz: number, tow: number): Vector4;

        lerp(to: Vector4, t: number): Vector4;
        lerp(tox: number, toy: number, toz: number, tow: number, t: number): Vector4;
    }

    class Sprite {
        position: Vector2;
        scale: Vector2;
        rotation: number;
    }


    var update: (delta: number) => void;
}

export default sw;