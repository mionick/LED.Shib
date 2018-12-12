import { Injectable } from '@angular/core';
import { LedConfiguration } from './led-config.class';
import { Observable } from 'rxjs';
import { HttpClient } from '@angular/common/http';

@Injectable()
export class LedConfigurationService {

  constructor(private http: HttpClient) { }

  public static LedUrl = "http://localhost:5000/lightconfig";

  public sendConfiguration(config: LedConfiguration): Observable<any> {
      return this.http.post<any>(LedConfigurationService.LedUrl, config);
  }

  public getConfiguration(): Observable<LedConfiguration> {
    return this.http.get<LedConfiguration>(LedConfigurationService.LedUrl);
  }

}