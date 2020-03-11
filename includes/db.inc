<?php
/**
 * Get entity form
 *
 * @return array
 */
function flat_access_request_form_get_form() {
    return node_load(variable_get('flat_access_request_form_id'));
}

/**
 * Fetch whether object is in exclusion list
 *
 * @param AbstractObject $object
 *
 * @return boolean
 */
function flat_access_request_form_excluded_object($object) {

    $pid       = trim(str_replace('info:fedora/', '', $object->id));
    $list      = variable_get('flat_access_request_form_exclusion_list');
    $list      = explode("\n", $list);
    $exclusion = [];

    foreach ($list as $item) {
        $exclusion[] = trim(str_replace('info:fedora/', '', $item));
    }

    return true === in_array($pid, $exclusion);
}

/**
 * check whether user has the webform roles
 *
 * @return boolean
 */
function flat_access_request_form_check_roles() {

    global $user;
    $node = flat_access_request_form_get_form();

    if (!$node) {

        // node not found
        return false;
    }

    $roles   = array_keys($user->roles);
    $allowed = false;

    foreach ($node->webform['roles'] as $role) {
        if (in_array($role, $roles)) {
            $allowed = true;
        }
    }

    return $allowed;
}

/**
 * Fetching all available webforms
 *
 * @return array
 */
function flat_access_request_form_get_webforms() {

    $query = db_select('webform', 'w');
    $query->join('node', 'n', 'w.nid = n.nid');
    $query->fields('n', ['nid', 'title']);

    return $query->execute()->fetchAllAssoc('nid');
}
