sliders = [
    dict(steps=[
        dict(method='animate',
             args=[[f'{k+1}'],
                   dict(mode='immediate',
                        frame=dict(duration=200, redraw=False),
                        transition=dict(duration=0)
                        )
                   ],
             label=f'day {k+1}'
             )
        for k in range(31)],
        transition=dict(duration=30),
        x=0,  # slider starting position
        y=0,
        currentvalue=dict(font=dict(size=12),
                          prefix='Day: ',
                          visible=True,
                          xanchor='center'
                          ),
        len=1.0)  # slider length)
]
