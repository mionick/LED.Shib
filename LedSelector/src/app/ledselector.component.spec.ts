import { TestBed, async } from '@angular/core/testing';
import { LedSelectorComponent } from './ledselector.component';

describe('LedSelectorComponent', () => {
  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [
        LedSelectorComponent
      ],
    }).compileComponents();
  }));

  it('should create the app', () => {
    const fixture = TestBed.createComponent(LedSelectorComponent);
    const app = fixture.debugElement.componentInstance;
    expect(app).toBeTruthy();
  });

  it(`should have as title 'LedSelector'`, () => {
    const fixture = TestBed.createComponent(LedSelectorComponent);
    const app = fixture.debugElement.componentInstance;
    expect(app.title).toEqual('LedSelector');
  });

  it('should render title in a h1 tag', () => {
    const fixture = TestBed.createComponent(LedSelectorComponent);
    fixture.detectChanges();
    const compiled = fixture.debugElement.nativeElement;
    expect(compiled.querySelector('h1').textContent).toContain('Welcome to LedSelector!');
  });
});
