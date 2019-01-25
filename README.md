# radndar
Gregorian Calendar Reversal and Opposition 

<p>I wanted to be able to celebrate Opposite Day (January 25th) in the most opposite way possible. So - as obsessive nerds like myself do - I whipped up a quick script to flip the year. After completion, I realized it wasn't as opposite as I wanted it - it was just reversed (ie: New Years Eve is on New Year's Day, New Year's Day is on New Year's Eve, Christmas is only a week after Christmas, Independence Day is only 4 days before itself, etc. etc. etc.) - so while opting to keep this option, and cleverly naming it, "RADNELAC", I ventured forth and tweaked the script to conform to a more opposite-like nature. Now, I am pleased to announce both the RADNELAC and the N-Darcale (another clever naming feat in the shadow of its predecessor) calendars!</p>
<p>Adding more holidays is always a nightmare of fun and enlightenment!</p>
<p>Feel free to enjoy RADNELAC's revealations! Your Reverse Father's Day (obviously, this one is for the kids - Dads, coin up! Reverse Father's Day is on its way!), the backwards Valentine's Day (the day for everybody else), and Citizen's Day (I mean really, who wants to celebrate Presidents?)</p>
<p>And - of course, we now have BOTH Reverse Opposite Day AND Opposite Opposite Day from that Red Bull juiced, amphetamine amped, armodafinil filled coded calendar horror we will all come to love dearly, The N-Darcale Calendar!</p>
<p>N-Darcale will bring such delights as Lazy Day, We Come in Peace and Won't Rape and Murder You - We're Not Columbus Day, White Monday, Thankless Taking, and the all-time classic, Satan Mas!</p>
<p>Enjoy your new found holidays, coded here first, at Phobos Technologies LLC :)</p>
<p>
  Basic usage is as follows:
</p>
  ```php
  /* $calendar can be either 'dnarcale' (the opposite calendar) or 'radnelac' (the reversed calendar) */
  $calendar = 'dnarcale';
  
  /* $format can be either 'text' for a full printout of the year, including an html highlight of today (guess I probably should have made that 'html' ... huh - whatever. OR, it can be 'ical' for an importable iCal file. */
  $format = 'text';
  
  /* Whatever calendar you decide to import must be in the following format where the array key is  'month.day' with no leading zeros for either. */
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

/* instantiate the object with what calendar you want and your holiday array */
$radnelac = new Radndar($calendar,$holidays_2019);

/* And finally, just let her know how you want that back :) Go nuts! */
echo $radnelac->get_calendar($format);
```
