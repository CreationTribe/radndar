<?PHP

if(isset($_GET['calendar'])) $calendar = $_GET['calendar'];
else $calendar = 'dnarcale';
if(isset($_GET['format'])) $format = $_GET['format'];
else $format = 'text';

include("radndar.inc");

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

$radnelac = new Radndar($calendar,$holidays_2019);
echo $radnelac->get_calendar($format);
