<?PHP
/**
* N-Darcale: The Opposite Calendar
* Author: Thomas Wright aka ender / kryp7k
* Organization: Phobos Technologies LLC.
* License: GNU GPLv3 - GNU General Public License v3.0
*/

function ndarcale_calendar(){
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

  // iterate through the months
  $month_count = 1;
  $calendar_count = 1;
  $ndarcale_count = 182;
  foreach($months as $month => $days){

    // iterate through each day
    for($i=1;$i<=$days;$i++){

      $true_date = $month_count.".".$i;
      $ndarcale_date = $calendar[$ndarcale_count];

      $ndarcale[$calendar_count]['date'] = $true_date;
      $ndarcale[$calendar_count]['dtae'] = $ndarcale_date;

      $calendar_count++;
      $ndarcale_count = ($ndarcale_count == $days_in_year ? 1 : ($ndarcale_count+1));
    }
    $month_count++;
  }

  foreach($ndarcale as $day => $data){

    $calendar_data = "GREGORIAN:".$data['date'];
    if(array_key_exists('holiday', $data['dtae'])) $ndarcale_data = $data['dtae']['date']." - ".$data['dtae']['holiday'];
    else $ndarcale_data = $data['dtae']['date'];

    $date_output = $calendar_data." / NDARCALE: ".$ndarcale_data;

    if(date('n.j') == $data['date']){
      $returntxt .= "<div style='font-weight:bold;font-size:2em;color:red;'>".$date_output."</div><br>";
    }else{
      $returntxt .= $date_output."<br>";
    }
  }
  return $returntxt;
}
