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



/**
 * Fetch whether user has no access
 *
 * @param AbstractObject $object
 *
 * @return boolean
 */
function flat_access_request_has_no_access($object = null) {

    if (null === $object) {
        return false;
    }

    global $user;

    module_load_include('inc', 'flat_permissions', 'includes/PermissionsAccess');

    $pid       = trim(str_replace('info:fedora/', '', $object->id));
    $list      = variable_get('flat_access_request_form_exclusion_list');
    $list      = explode("\n", $list);
    $exclusion = [];

    foreach ($list as $item) {
        $exclusion[] = trim(str_replace('info:fedora/', '', $item));
    }

    return false === in_array($pid, $exclusion) && false === PermissionsAccess::hasAccess($user, $object, new IslandoraXacml($object));
}
