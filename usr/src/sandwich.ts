declare namespace sw {
    namespace math {
        class Vector2 {
            x: number;
            y: number;

            constructor();
            constructor(scalar: number);
            constructor(x: number, y: number);
            constructor(other: Vector2);

            angle(x: number, y: number): number;
            angle(other: Vector2): number;
            determinant(x: number, y: number): number;
            determinant(other: Vector2): number;
            distance(x: number, y: number): number;
            distance(other: Vector2): number;
            distanceSquared(x: number, y: number): number;
            distanceSquared(other: Vector2): number;
            dot(x: number, y: number): number;
            dot(other: Vector2): number;
            length(): number;
            lengthSquared(): number;

            lerp(x: number, y: number, t: number): Vector2;
            lerp(other: Vector2, t: number): Vector2;
            max(x: number, y: number): Vector2;
            max(other: Vector2): Vector2;
            min(x: number, y: number): Vector2;
            min(other: Vector2): Vector2;
            normalized(): Vector2;
            perpendicular(): Vector2;

            negated(): Vector2;

            ceil(): Vector2;
            floor(): Vector2;
            normalize(): Vector2;
            round(): Vector2;
            set(scalar: number): Vector2;
            set(x: number, y: number): Vector2;
            set(other: Vector2): Vector2;
            zero(): Vector2;

            add(scalar: number): Vector2;
            sub(scalar: number): Vector2;
            mul(scalar: number): Vector2;
            div(scalar: number): Vector2;
            add(other: Vector2): Vector2;
            sub(other: Vector2): Vector2;
            mul(other: Vector2): Vector2;
            div(other: Vector2): Vector2;

            static add(v1: Vector2, v2: Vector2): Vector2;
            static sub(v1: Vector2, v2: Vector2): Vector2;
            static mul(v1: Vector2, v2: Vector2): Vector2;
            static div(v1: Vector2, v2: Vector2): Vector2;
        }

        class Vector3 {
            x: number;
            y: number;
            z: number;

            constructor();
            constructor(scalar: number);
            constructor(x: number, y: number, z: number);
            constructor(other: Vector3);
            constructor(other: Vector2, z: number);

            angle(x: number, y: number, z: number): number;
            angle(other: Vector3): number;
            angleCos(x: number, y: number, z: number): number;
            angleCos(other: Vector3): number;
            distance(x: number, y: number, z: number): number;
            distance(other: Vector3): number;
            distanceSquared(x: number, y: number, z: number): number;
            distanceSquared(other: Vector3): number;
            dot(x: number, y: number, z: number): number;
            dot(other: Vector3): number;
            length(): number;
            lengthSquared(): number;

            cross(x: number, y: number, z: number): Vector3;
            cross(other: Vector3): Vector3;
            lerp(x: number, y: number, z: number, t: number): Vector3;
            lerp(other: Vector3, t: number): Vector3;
            max(x: number, y: number, z: number): Vector3;
            max(other: Vector3): Vector3;
            min(x: number, y: number, z: number): Vector3;
            min(other: Vector3): Vector3;
            normalized(): Vector3;

            negated(): Vector3;

            ceil(): Vector3;
            floor(): Vector3;
            normalize(): Vector3;
            round(): Vector3;
            set(scalar: number): Vector3;
            set(x: number, y: number, z: number): Vector3;
            set(other: Vector3): Vector3;
            set(other: Vector2, z: number): Vector3;
            zero(): Vector3;

            add(scalar: number): Vector3;
            sub(scalar: number): Vector3;
            mul(scalar: number): Vector3;
            div(scalar: number): Vector3;
            add(other: Vector3): Vector3;
            sub(other: Vector3): Vector3;
            mul(other: Vector3): Vector3;
            div(other: Vector3): Vector3;

            static add(v1: Vector3, v2: Vector3): Vector3;
            static sub(v1: Vector3, v2: Vector3): Vector3;
            static mul(v1: Vector3, v2: Vector3): Vector3;
            static div(v1: Vector3, v2: Vector3): Vector3;
        }

        class Vector4 {
            x: number;
            y: number;
            z: number;
            w: number;

            constructor();
            constructor(scalar: number);
            constructor(x: number, y: number, z: number, w: number);
            constructor(other: Vector4);
            constructor(other: Vector3, w: number);
            constructor(other: Vector2, z: number, w: number);

            angle(x: number, y: number, z: number, w: number): number;
            angle(other: Vector4): number;
            angleCos(x: number, y: number, z: number, w: number): number;
            angleCos(other: Vector4): number;
            distance(x: number, y: number, z: number, w: number): number;
            distance(other: Vector4): number;
            distanceSquared(x: number, y: number, z: number, w: number): number;
            distanceSquared(other: Vector4): number;
            dot(x: number, y: number, z: number, w: number): number;
            dot(other: Vector4): number;
            length(): number;
            lengthSquared(): number;

            lerp(x: number, y: number, z: number, w: number, t: number): Vector4;
            lerp(other: Vector4, t: number): Vector4;
            max(x: number, y: number, z: number, w: number): Vector4;
            max(other: Vector4): Vector4;
            min(x: number, y: number, z: number, w: number): Vector4;
            min(other: Vector4): Vector4;
            normalized(): Vector4;

            negated(): Vector4;

            ceil(): Vector4;
            floor(): Vector4;
            normalize(): Vector4;
            round(): Vector4;
            set(scalar: number): Vector4;
            set(x: number, y: number, z: number, w: number): Vector4;
            set(other: Vector4): Vector4;
            set(other: Vector3, w: number): Vector4;
            set(other: Vector2, z: number, w: number): Vector4;
            zero(): Vector4;

            add(scalar: number): Vector4;
            sub(scalar: number): Vector4;
            mul(scalar: number): Vector4;
            div(scalar: number): Vector4;
            add(other: Vector4): Vector4;
            sub(other: Vector4): Vector4;
            mul(other: Vector4): Vector4;
            div(other: Vector4): Vector4;

            static add(v1: Vector4, v2: Vector4): Vector4;
            static sub(v1: Vector4, v2: Vector4): Vector4;
            static mul(v1: Vector4, v2: Vector4): Vector4;
            static div(v1: Vector4, v2: Vector4): Vector4;
        }

        class AxisAngle {
            axis: Vector3;
            angle: number;

            constructor();
            constructor(angle: number, x: number, y: number, z: number);
            constructor(angle: number, axis: Vector3);
            constructor(other: AxisAngle);

            rotate(angle: number): AxisAngle;

            set(angle: number, x: number, y: number, z: number): AxisAngle;
            set(angle: number, axis: Vector3): AxisAngle;
            set(other: AxisAngle): AxisAngle;
        }

        class Matrix4 {
            m: number[];

            constructor();
            constructor(data: number[]);
            constructor(m00: number, m01: number, m02: number, m03: number,
                        m10: number, m11: number, m12: number, m13: number,
                        m20: number, m21: number, m22: number, m23: number,
                        m30: number, m31: number, m32: number, m33: number);
            constructor(other: Matrix4);

            identity(): Matrix4;
            invert(): Matrix4;
            rotate(angle: number, x: number, y: number, z: number): Matrix4;
            rotate(angle: number, axis: Vector3): Matrix4;
            rotate(axisAngle: AxisAngle): Matrix4;
            scale(x: number, y: number, z: number): Matrix4;
            scale(scale: Vector3): Matrix4;
            translate(x: number, y: number, z: number): Matrix4;
            translate(translation: Vector3): Matrix4;
            transpose(): Matrix4;

            set(data: number): Matrix4;
            set(m00: number, m01: number, m02: number, m03: number,
                m10: number, m11: number, m12: number, m13: number,
                m20: number, m21: number, m22: number, m23: number,
                m30: number, m31: number, m32: number, m33: number): Matrix4;
            set(other: Matrix4): Matrix4;


            setOrtho(left: number, right: number, bottom: number, top: number,
                     zNear: number, zFar: number): Matrix4;
            setOrtho(left: number, right: number, bottom: number, top: number,
                     zNear: number, zFar: number, zZeroToOne: boolean): Matrix4;
            setOrtho2D(left: number, right: number, bottom: number, top: number): Matrix4;
            setPerspective(fovY: number, aspect: number,
                           zNear: number, zFar: number): Matrix4;
            setPerspective(fovY: number, aspect: number,
                           zNear: number, zFar: number, zZeroToOne: boolean): Matrix4;

            getRotation(): AxisAngle;
            getScale(): Vector3;
            getTranslation(): Vector3;

            determinant(): number;

            mul(other: Matrix4): Matrix4;
            transform(v: Vector4): Vector4;
        }
    }

    class TextureData {
        constructor(width: number, height: number);

        setPixel(x: number, y: number, r: number, g: number, b: number, a: number): void;
    }

    class Texture {
        static create(data: TextureData): Texture;
    }

    class SpriteBatch {
        constructor();
        setProjectionMatrix(matrix: math.Matrix4): void;
        begin(): void;
        end(): void;
        draw(texture: Texture, x: number, y: number, rotation: number,
             origin_x: number, origin_y: number, scale_x: number, scale_y: number,
             flip_x: boolean, flip_y: boolean): void;
    }

    class Sprite {
        position: math.Vector2;
        scale: math.Vector2;
        rotation: number;
    }

    class Screen {
        static readonly width: number;
        static readonly height: number;

        static mode: Screen.ScreenMode;

        static getTitle(): string;
        static setTitle(title: string): void;

        static setMode(mode: Screen.ScreenMode, refreshRate: number): void;
        static setResolution(width: number, height: number,
                             screenMode: Screen.ScreenMode, refreshRate: number): void;

        static getSupportedFullscreenResolutions(): Screen.Resolution[];
    }

    namespace Screen {
        class Resolution {
            readonly width: number;
            readonly height: number;
            readonly refreshRate: number;
        }

        enum ScreenMode {
            WINDOWED,
            FULLSCREEN,
            BORDERLESS_WINDOW
        }
    }

    let init: () => void;
    let update: (delta: number) => void;
}

export default sw;