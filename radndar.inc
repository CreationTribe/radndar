<?PHP
/**
* RADNDAR: Combines RADNELAC and N-Darcale Calendars
* Author: Thomas Wright aka ender / kryp7k
* Organization: Phobos Technologies LLC.
* License: GNU GPLv3 - GNU General Public License v3.0
*
* Thanks to Jake Bellacera - from whom I borrowed the ICS.inc class
* for injecting these whacky cals straight straight into the vein.
*   https://gist.github.com/jakebellacera
*   https://gist.github.com/jakebellacera/635416
*
*/
class Radndar{



  private $leapyear;
  private $feb_days;
  private $days_in_year;
  private $months;
  private $calendar_type;
  private $alt_cal;

  public function __construct($calendar_type='ndarcale',$holidays){

    $this->calendar_type = strtoupper($calendar_type);

    // arrange for the possibility of leapyear
    $this->leapyear = date('L');
    $this->feb_days = ($this->leapyear ? 29 : 28);
    $this->days_in_year = ($this->leapyear ? 366 : 365);

    // layout month spans accordingly
    $this->months = array(  'January'   =>  31,
                      'February'  =>  $this->feb_days,
                      'March'     =>  31,
                      'April'     =>  30,
                      'May'       =>  31,
                      'June'      =>  30,
                      'July'      =>  31,
                      'August'    =>  31,
                      'September' =>  30,
                      'October'   =>  31,
                      'November'  =>  30,
                      'December'  =>  31);

    $gcal = $this->build_gregorian_cal($holidays);

    if($calendar_type == 'ndarcale'){
      $this->alt_cal = $this->build_ndarcale_cal($holidays,$gcal);
    }elseif($calendar_type == 'radnelac'){
      $this->alt_cal = $this->build_radnelac_cal($holidays,$gcal);
    }else{
      throw new Exception("Unknown calendar type requested (valid types: 'ndarcale' or 'radnelac')");
    }
  }

  private function build_gregorian_cal($holidays){
    // iterate through the months
    $month_count = 1;
    $calendar_count = 1;
    foreach($this->months as $month => $days){

      // iterate through each day
      for($i=1;$i<=$days;$i++){

        // see if there is a holiday's key that matches
        $date = $month_count.".".$i;
        if(array_key_exists($date,$holidays)){
          $calendar[$calendar_count]['date'] = $date;
          $calendar[$calendar_count]['holiday'] = $holidays[$date];
        }else{
          $calendar[$calendar_count]['date'] = $date;
        }
        $calendar_count++;
      }
      $month_count++;
    }
    return $calendar;
  }

  private function build_radnelac_cal($holidays,$calendar){
    $month_count = 1;
    $calendar_count = 1;
    $radnelac_count = $this->days_in_year;
    foreach($this->months as $month => $days){

      // iterate through each day
      for($i=1;$i<=$days;$i++){

        $true_date = $month_count.".".$i;
        $radnelac_date = $calendar[$radnelac_count];

        $radnelac[$calendar_count]['date'] = $true_date;
        $radnelac[$calendar_count]['alt'] = $radnelac_date;

        $calendar_count++;
        $radnelac_count--;
      }
      $month_count++;
    }
    return $radnelac;
  }

  private function build_ndarcale_cal($holidays,$calendar){
    // iterate through the months
    $month_count = 1;
    $calendar_count = 1;
    $ndarcale_count = 182;
    foreach($this->months as $month => $days){

      // iterate through each day
      for($i=1;$i<=$days;$i++){

        $true_date = $month_count.".".$i;
        $ndarcale_date = $calendar[$ndarcale_count];

        $ndarcale[$calendar_count]['date'] = $true_date;
        $ndarcale[$calendar_count]['alt'] = $ndarcale_date;

        $calendar_count++;
        $ndarcale_count = ($ndarcale_count == $this->days_in_year ? 1 : ($ndarcale_count+1));
      }
      $month_count++;
    }
    return $ndarcale;
  }

  public function get_calendar($output){

    $returntxt='';

    if($output == 'text'){
      $returntxt = $this->text_format();
    }elseif($output == 'ical'){
      $returntxt = $this->ical_format();
    }else{
      throw new Exception("Unknown return format requested (valid formats: 'text' or 'ical')");
    }
    return $returntxt;
  }

  private function text_format(){

    $returntxt='';

    foreach($this->alt_cal as $day => $data){

      $calendar_data = "GREGORIAN:".$data['date'];

      if(array_key_exists('holiday', $data['alt'])) $radndar_data = $data['alt']['date']." - ".$data['alt']['holiday'];
      else $radndar_data = $data['alt']['date'];

      $date_output = $calendar_data." / $this->calendar_type: ".$radndar_data;

      if(date('n.j') == $data['date']){
        $returntxt .= "<div style='font-weight:bold;font-size:2em;color:red;'>".$date_output."</div><br>";
      }else{
        $returntxt .= $date_output."<br>";
      }
    }
    return $returntxt;
  }

  private function ical_format(){

    /* TO FOLLOW THE FOLLOWING FORMAT *****************/

    // BEGIN:VCALENDAR
    // PRODID:-//Google Inc//Google Calendar 70.9054//EN
    // VERSION:2.0
    // CALSCALE:GREGORIAN
    // METHOD:PUBLISH
    // X-WR-TIMEZONE:America/Denver
    //
    // BEGIN:VEVENT
    // DTSTART;VALUE=DATE:20181109
    // DTEND;VALUE=DATE:20181110
    // DTSTAMP:20190123T032352Z
    // UID:2018_BIRTHDAY_self@google.com
    // CLASS:PUBLIC
    // CREATED:20180430T163932Z
    // DESCRIPTION:Happy birthday!
    // SEQUENCE:0
    // STATUS:CONFIRMED
    // SUMMARY:Happy birthday!
    // TRANSP:OPAQUE
    // END:VEVENT
    //
    // END:VCALENDAR

    $returntxt =  "BEGIN:VCALENDAR\r\n".
                  "PRODID:-//Google Inc//Google Calendar 70.9054//EN\r\n".
                  "VERSION:2.0\r\n".
                  "CALSCALE:GREGORIAN\r\n".
                  "METHOD:PUBLISH\r\n".
                  "X-WR-TIMEZONE:America/Denver\r\n";

    foreach($this->alt_cal as $day => $data){

      // $data: array(2) { ["date"]=> string(3) "1.8" ["alt"]=> array(2) { ["date"]=> string(5) "12.24" ["holiday"]=> string(13) "Christmas Eve" } }
      if(array_key_exists('holiday', $data['alt'])){
        $date = $data['date'];
        $holiday = $data['alt']['holiday'];

        $datesploded = explode('.',$date);
        $holiday_month = $datesploded[0];
        $holiday_day = $datesploded[1];

        $returntxt .= "BEGIN:VEVENT\r\n".
                      "DTSTART;VALUE=DATE:".date('Ymd',mktime(0,0,0,$holiday_month,$holiday_day,date('Y')))."\r\n".
                      "DTEND;VALUE=DATE:".date('Ymd',mktime(0,0,0,$holiday_month,($holiday_day+1),date('Y')))."\r\n".
                      "DTSTAMP:".date("Ymd\THis\Z")."\r\n".
                      "UID:".date('Y').'_'.$holiday."\r\n".
                      "CLASS:PUBLIC\r\n".
                      "CREATED:".date("Ymd\THis\Z")."\r\n".
                      "DESCRIPTION:".$holiday."\r\n".
                      "SEQUENCE:0\r\n".
                      "STATUS:CONFIRMED\r\n".
                      "SUMMARY:".$holiday."\r\n".
                      "TRANSP:OPAQUE\r\n".
                      "END:VEVENT\r\n";
      }

    }
    $returntxt .= "END:VCALENDAR\r\n";
    return $returntxt;
  }
}
