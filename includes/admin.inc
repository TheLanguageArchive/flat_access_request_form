<?php
/**
 * Admin form
 *
 * @param array $form
 * @param array $form_state
 *
 * @return array
 */
function flat_access_request_form_admin_form($form, &$form_state) {

    $form = [

        'general' => [

            '#type'  => 'fieldset',
            '#title' => t('General'),
            'title'  => [

                '#type'          => 'textfield',
                '#title'         => 'Title',
                '#help_text'     => 'Fill in form title that needs to be displayed when requesting access',
                '#size'          => 30,
                '#default_value' => variable_get('flat_access_request_form_title'),
            ],

            'exclusion_list' => [

                '#type'          => 'textarea',
                '#title'         => 'Exclusion list',
                '#help_text'     => 'Please fill in a list of Fedora PID, separated by line delimeter',
                '#size'          => 30,
                '#default_value' => variable_get('flat_access_request_form_exclusion_list'),
            ],
        ],

        'actions' => [

            '#type'  => 'actions',
            'submit' => [

                '#type'   => 'submit',
                '#value'  => t('Save Configuration'),
                '#weight' => 0,
                '#submit' => ['flat_access_request_form_admin_form_submit'],
            ],

            'reset' => [

                '#type'   => 'submit',
                '#value'  => t('Reset to defaults'),
                '#weight' => 1,
                '#submit' => ['flat_access_request_form_admin_form_submit'],
            ],
        ],
    ];

    return $form;
}

/**
 * Admin Form submit
 *
 * @param array $form
 * @param array $form_state
 *
 * @return void
 */
function flat_access_request_form_admin_form_submit($form, &$form_state) {

    if ($form_state['triggering_element']['#value'] == t('Reset to defaults')) {

        variable_set('flat_access_request_form_title', t('Flat Access Request Form'));
        variable_set('flat_access_request_form_exclusion_list', '');

        $form_state['redirect'] = 'admin/config/flat_deposit/flat_access_request_form';
        drupal_set_message(t('FLAT access request form admin configuration was successfully reset to defaults'));

    } else {

        variable_set('flat_access_request_form_title', $form_state['values']['title']);
        variable_set('flat_access_request_form_exclusion_list', $form_state['values']['exclusion_list']);

        drupal_set_message(t('FLAT request access admin configuration was successfully saved'));
    }
}
