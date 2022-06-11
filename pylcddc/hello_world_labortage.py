import pylcddc.client as client
import pylcddc.widgets as widgets
import pylcddc.screen as screen

title = widgets.Title('title_widget',
                      'Labortage \'21')
main_scr = screen.Screen('main', [title])

c = client.Client('localhost', 13666)
c.add_screen(main_scr)
input('Press any key to exit')
c.close()
