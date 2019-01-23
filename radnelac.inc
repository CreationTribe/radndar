<?PHP
/**
* RADNELAC: The Backward Calendar
* Author: Thomas Wright aka ender / kryp7k
* Organization: Phobos Technologies LLC.
* License: GNU GPLv3 - GNU General Public License v3.0
*/

function radnelac_calendar(){
  $leapyear = date('L');

  $feb_days = ($leapyear ? 29 : 28);
  $days_in_year = ($leapyear ? 366 : 365);

  $days_count_up = 1;

  $returntxt = '';

  $months = array(  'January'   =>  31,
                    'February'  =>  $feb_days,
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

  $holidays_2019 = array( '1.1'   => "New Year's Day",
                          '1.21'  => "Martin Luther King Jr. Day",
                          '1.25'  => "Opposite Day",
                          '2.14'  => "Valentine's Day",
                          '2.18'  => "President's Day",
                          '3.17'  => "St. Patrick's Day",
                          '4.15'  => "Tax Day",
                          '4.21'  => "Easter Sunday",
                          '4.22'  => "Easter Monday",
                          '5.5'   => "Cinco de Mayo",
                          '5.12'  => "Mother's Day",
                          '5.27'  => "Memorial Day",
                          '6.16'  => "Father's Day",
                          '7.4'   => "Independence Day",
                          '9.2'   => "Labor Day",
                          '10.14' => "Columbus Day",
                          '10.31' => "Halloween",
                          '11.11' => "Veterans Day",
                          '11.28' => "Thanksgiving Day",
                          '11.29' => "Black Friday",
                          '12.24' => "Christmas Eve",
                          '12.25' => "Christmas Day",
                          '12.31' => "New Year's Eve");

  // iterate through the months
  $month_count = 1;
  $calendar_count = 1;
  foreach($months as $month => $days){

    // iterate through each day
    for($i=1;$i<=$days;$i++){

      // see if there is a holiday's key that matches
      $date = $month_count.".".$i;
      if(array_key_exists($date,$holidays_2019)){
        $calendar[$calendar_count]['date'] = $date;
        $calendar[$calendar_count]['holiday'] = $holidays_2019[$date];
      }else{
        $calendar[$calendar_count]['date'] = $date;
      }
      $calendar_count++;
    }
    $month_count++;
  }

  $month_count = 1;
  $calendar_count = 1;
  $radnelac_count = $days_in_year;
  foreach($months as $month => $days){

    // iterate through each day
    for($i=1;$i<=$days;$i++){

      $true_date = $month_count.".".$i;
      $radnelac_date = $calendar[$radnelac_count];

      $radnelac[$calendar_count]['date'] = $true_date;
      $radnelac[$calendar_count]['etad'] = $radnelac_date;

      $calendar_count++;
      $radnelac_count--;
    }
    $month_count++;
  }

  foreach($radnelac as $day => $data){

    $calendar_data = "GREGORIAN:".$data['date'];
    if(array_key_exists('holiday', $data['etad'])) $radnelac_data = $data['etad']['date']." - ".$data['etad']['holiday'];
    else $radnelac_data = $data['etad']['date'];

    $date_output = $calendar_data." / RADNELAC: ".$radnelac_data;

    if(date('n.j') == $data['date']){
      $returntxt .= "<div style='font-weight:bold;font-size:2em;color:red;'>".$date_output."</div><br>";
    }else{
      $returntxt .= $date_output."<br>";
    }
  }
  return $returntxt;
}

// Jan 1	Tuesday	New Year's Day	Federal Holiday
// Jan 21	Monday	Martin Luther King Jr. Day	Federal Holiday
// Jan 25  Friday Opposite Day
// Feb 14	Thursday	Valentine's Day	Observance
// Feb 18	Monday	Presidents' Day	Federal Holiday	All except DE, GA, IA, IN, KS, KY, LA, NC, NM, RI, WI
// Mar 17	Sunday	St. Patrick's Day	Observance, Christian
// Apr 15	Monday	Tax Day	Observance
// Apr 21	Sunday	Easter Sunday	Observance, Christian
// Apr 22	Monday	Easter Monday	Observance, Christian
// May 5	Sunday	Cinco de Mayo	Observance
// May 12	Sunday	Mother's Day	Observance
// May 27	Monday	Memorial Day	Federal Holiday
// Jun 16	Sunday	Father's Day	Observance
// Jul 4	Thursday	Independence Day	Federal Holiday
// Sep 2	Monday	Labor Day	Federal Holiday
// Oct 14	Monday	Columbus Day	Federal Holiday	All except AK, AR, CA, DE, FL, HI, MI, MN, ND, NV, OR, SD, TX, VT, WA, WY
// Oct 31	Thursday	Halloween	Observance
// Nov 11	Monday	Veterans Day	Federal Holiday
// Nov 28	Thursday	Thanksgiving Day	Federal Holiday
// Nov 29	Friday	Black Friday	Observance
// Dec 24	Tuesday	Christmas Eve	Observance, Christian
// Dec 25	Wednesday	Christmas Day	Federal Holiday
// Dec 31	Tuesday	New Year's Eve	Observance
