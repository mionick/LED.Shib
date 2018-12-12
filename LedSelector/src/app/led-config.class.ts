export class LedConfiguration {
    constructor(
        public rgb: number[] = [255, 255, 255],
        public isRainbow: boolean = false,
        public isSolid: boolean = false,
        public strength: number = 1,
        public speed: number = 0.01,
        public angularSpeed: number = 1
    ){}
}