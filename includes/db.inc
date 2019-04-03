<?php
/**
 * Get entity form
 *
 * @return array
 */
function flat_access_request_form_entity() {

    $query = new EntityFieldQuery();

    return $query->entityCondition('entity_type', 'node')
        ->propertyCondition('type', 'webform')
        ->propertyCondition('title', variable_get('flat_access_request_form_title'))
        ->propertyCondition('status', 1)
        ->range(0, 1)
        ->execute();
}
