import { BrowserModule } from '@angular/platform-browser';
import { NgModule, Injector, CUSTOM_ELEMENTS_SCHEMA } from '@angular/core';
import { createCustomElement } from '@angular/elements';
import { FormsModule } from '@angular/forms';
import { HttpClientModule } from '@angular/common/http';

import { LedSelectorComponent } from './ledselector.component';
import { LedConfigurationService } from 'src/app/led-configuration.service';

@NgModule({
  declarations: [
    LedSelectorComponent
  ],
  imports: [
    BrowserModule,
    FormsModule,
    HttpClientModule

  ],
  providers: [ LedConfigurationService ],
  entryComponents: [LedSelectorComponent],
  schemas: [CUSTOM_ELEMENTS_SCHEMA]
})
export class AppModule {
  constructor(private injector: Injector) {
  }
  
  
  ngDoBootstrap() {
    const myCustomElement = createCustomElement(LedSelectorComponent, { injector: this.injector });
    customElements.define('ng-led-selector', myCustomElement);
  }
}
