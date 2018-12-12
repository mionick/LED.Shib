import { Component } from '@angular/core';
import Pickr from 'pickr-widget'
import { LedConfiguration } from './led-config.class';
import { LedConfigurationService } from 'src/app/led-configuration.service';

@Component({
  selector: 'led-selector',
  templateUrl: './ledselector.component.html',
  styleUrls: ['./ledselector.component.scss']
})
export class LedSelectorComponent {
  
  public ledConfig: LedConfiguration = new LedConfiguration();

  constructor(private ledConfigurationService: LedConfigurationService) {

  }

  ngOnInit() {
    this.ledConfigurationService.getConfiguration().subscribe( x=> this.ledConfig = x);

    const pickr = new Pickr({
      el: '#color-picker',
    
      // Using the 'el' Element as button, won't replace it with the pickr-button.
      // If true, appendToBody will also be automatically true.
      useAsButton: false,
    
      // Start state. If true 'disabled' will be added to the button's classlist.
      disabled: false,
    
      // If set to false it would directly apply the selected color on the button and preview.
      comparison: true,
    
      // Default color
      default: 'fff',
    
      // Option to keep the color picker always visible. You can still hide / show it via
      // 'pickr.hide()' and 'pickr.show()'. The save button keeps his functionality, so if
      // you click it, it will fire the onSave event.
      showAlways: false,
    
      // Defines a parent for pickr, if useAsButton is true and a parent is NOT defined
      // 'body' will be used as fallback.
      parent: null,
    
      // Close pickr with this specific key.
      // Default is 'Escape'. Can be the event key or code.
      closeWithKey: 'Escape',
    
      // Defines the position of the color-picker. Available options are
      // top, left and middle relativ to the picker button.
      // If clipping occurs, the color picker will automatically choose his position.
      position: 'middle',
    
      // Enables the ability to change numbers in an input field with the scroll-wheel.
      // To use it set the cursor on a position where a number is and scroll, use ctrl to make steps of five
      adjustableNumbers: true,
    
      // Show or hide specific components.
      // By default only the palette (and the save button) is visible.
      components: {
    
          preview: true, // Left side color comparison
          opacity: false, // Opacity slider
          hue: true,     // Hue slider
    
          // Bottom interaction bar, theoretically you could use 'true' as propery.
          // But this would also hide the save-button.
          interaction: {
              hex: true,  // hex option  (hexadecimal representation of the rgba value)
              rgba: true, // rgba option (red green blue and alpha)
              hsla: true, // hsla option (hue saturation lightness and alpha)
              hsva: true, // hsva option (hue saturation value and alpha)
              cmyk: false, // cmyk option (cyan mangenta yellow key )
    
              input: true, // input / output element
              clear: false, // Button which provides the ability to select no color,
              save: true   // Save button
          },
      },
    
      // Button strings, brings the possibility to use a language other than English.
      strings: {
          save: 'Save',  // Default for save button
          clear: 'Clear' // Default for clear button
      }
    });

    document.getElementsByClassName("pcr-save")[0]
    .addEventListener( 'click', 
    () => { 
      let rgba = pickr.getColor().toRGBA();
      this.ledConfig.rgb = [
        this.sanitizeRgbNumber(rgba[0]),
        this.sanitizeRgbNumber(rgba[1]),
        this.sanitizeRgbNumber(rgba[2])
      ]
    })
      
  }

  /** Ensures a number is an integer and is between 0 and 255 */
  private sanitizeRgbNumber(x: number) {
    return Math.min(Math.max(Math.floor(x), 0), 255)
  }

  public sendConfig() {
    this.ledConfigurationService.sendConfiguration(this.ledConfig).subscribe();
  }

}
