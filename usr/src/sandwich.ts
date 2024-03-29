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

    class Screen {
        static readonly width: number;
        static readonly height: number;

        static title: string;
        static mode: Screen.ScreenMode;

        static setMode(mode: Screen.ScreenMode, refreshRate: number): void;
        static setResolution(width: number, height: number): void;
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
            Windowed,
            Fullscreen,
            BorderlessWindow
        }
    }

    class Shader {
        readonly uniforms: { [name: string]: Shader.Uniform; }
        getUniform(name: string): Shader.Uniform;

        readonly attributes: { [name: string]: Shader.Attribute; }
        getAttribute(name: string): Shader.Attribute;

        bind(): void;

        static fromSource(sources: { [S in Shader.Stage]: string; }): Shader;
    }

    namespace Shader {
        enum Stage {
            Vertex,
            Fragment,
            Geometry
        }

        enum ValueType {
            Float,
            Int,
            UnsignedInt,
            Matrix3Float,
            Matrix4Float,
            Vector2Float,
            Vector3Float,
            Vector4Float,
            Vector2Int,
            Vector3Int,
            Vector4Int,
            Vector2UnsignedInt,
            Vector3UnsignedInt,
            Vector4UnsignedInt,
            TextureUnit,
            Unsupported
        }

        class Attribute {
            readonly name: string;
            readonly type: ValueType;
            readonly location: number;
        }

        class Uniform {
            readonly name: string;
            readonly type: ValueType;
            readonly location: number;

            set(v: number): void;
            set(vec: math.Vector2): void;
            set(vec: math.Vector3): void;
            set(vec: math.Vector4): void;
            set(vec: math.Matrix4): void;
        }
    }

    class SpriteBatch {
        color: math.Vector4;
        shader: Shader;
        viewMatrix: math.Matrix4;
        projectionMatrix: math.Matrix4;

        constructor();

        begin(): void;
        flush(): void;
        end(): void;

        draw(texture: Texture | TextureRegion, x: number, y: number, rotation: number,
             originX: number, originY: number, scaleX: number, scaleY: number,
             flipX: boolean, flipY: boolean): void;

        draw(texture: Texture | TextureRegion, position: math.Vector2, rotation: number,
             origin: math.Vector2, scale: math.Vector2,
             flipX: boolean, flipY: boolean): void;
    }

    class TextureData {
        format: TextureData.Format;
        width: number;
        height: number;

        constructor(width: number, height: number);
        constructor(width: number, height: number, format: TextureData.Format);
        constructor(textureData: TextureData);

        set(textureData: TextureData): void;

        getPixel(x: number, y: number): math.Vector4;

        setPixel(x: number, y: number, r: number, g: number, b: number): void;
        setPixel(x: number, y: number, r: number, g: number, b: number, a: number): void;
        setPixel(x: number, y: number, color: math.Vector4): void;

        setRect(x: number, y: number, rect: TextureData): void;
        setRect(x: number, y: number, rect: TextureData,
                srcX: number, srcY: number, srcWidth: number, srcHeight: number): void;

        fill(r: number, g: number, b: number): void;
        fill(r: number, g: number, b: number, a: number): void;
        fill(color: math.Vector4): void;

        flipHorizontally(): void;
        flipVertically(): void;
    }

    namespace TextureData {
        enum Format {
            RGBA8888,
            RGB888,
            RGB565,
            RGBA4444
        }
    }

    class Texture {
        readonly width: number;
        readonly height: number;

        readonly haveMipmap: boolean;
        readonly loaded: boolean;

        filtering: Texture.Filtering;
        wrapping: Texture.Wrapping;

        data: TextureData;

        genMipmap(): void;
        load(): void;
        unload(): void;
        reload(): void;
        bind(): void;

        static create(data: TextureData): Texture;
    }

    namespace Texture {
        enum Filtering {
            Nearest,
            Linear,
            Trilinear
        }

        enum Wrapping {
            Edge,
            Repeat,
            Mirror
        }
    }

    class TextureRegion {
        texture: Texture;
        x: number;
        y: number;
        width: number;
        height: number;
        flipX: boolean;
        flipY: boolean;
        readonly uvUpper: math.Vector2;
        readonly uvLower: math.Vector2;

        constructor();
        constructor(texture: Texture);
        constructor(texture: Texture, x: number, y: number, width: number, height: number);
        constructor(textureRegion: TextureRegion);

        set(textureRegion: TextureRegion): void;
    }

    let init: () => void;
    let update: (delta: number) => void;
}

export default sw;