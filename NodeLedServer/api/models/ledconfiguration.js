class LedConfiguration {
    constructor(
        rgb = [255, 255, 255],
        isRainbow = false,
        isSolid = false,
        strength = 1,
        speed = 0.01,
        angularSpeed = 1
    )
    {
        this.rgb = rgb;
        this.isRainbow      =         isRainbow;
        this.isSolid        =         isSolid;
        this.strength       =         strength; 
        this.speed          =         speed;
        this.angularSpeed   =         angularSpeed;

    };

    toArduinoString() {
        var output = "r" + ( this.isRainbow ? 1 : 0)
        output += "s" + ( this.isSolid ? 1 : 0)
        output += "S" + ( this.speed )
        output += "R" + ( this.rgb[0])
        output += "G" + ( this.rgb[1])
        output += "B" + ( this.rgb[2])
        output += "b" + ( this.strength)
        output += "a" + ( this.angularSpeed)
        return output;
    }
}

module.exports = LedConfiguration;